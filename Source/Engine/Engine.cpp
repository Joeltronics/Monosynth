/*
  ==============================================================================

    Engine.cpp
    Created: 7 Sep 2015 12:30:58pm
    Author:  Joel Geddert

  ==============================================================================
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Engine.h"

#include "JuceHeader.h"

#include "Types.h"

#include "Utils/ApproxEqual.h"
#include "Utils/DspUtils.h"
#include "Utils/Resampling.h"
#include "Utils/Logger.h"

namespace Engine {
	const double k_filtCvCutoff_Hz = 10.0;
	float k_vcoRandPitchAmt = 0.01f; // In semitones
	float k_filtCutoffRandAmt_semi = 0.05f; // In semitones
}

namespace Detail {
	static Engine::waveform_t MainOscToWave(size_t n) {
		switch (n) { // tri/rect/saw
		case 0: return Engine::waveShape_tri; break;
		case 1: return Engine::waveShape_pwm; break;
		case 2: return Engine::waveShape_saw; break;
		default: DEBUG_ASSERT(false);
			return Engine::waveShape_saw;
		}
	}

	static Engine::waveform_t SubOscToWave(size_t n) {
		switch (n) { // tri/squ/pulse
		case 0: return Engine::waveShape_tri;
		case 1: return Engine::waveShape_squ50;
		case 2: return Engine::waveShape_pulse25;
		default: DEBUG_ASSERT(false);
			return Engine::waveShape_tri;
		}
	}

	static Engine::filterModel_t ConvertFiltModel(size_t n)
	{
		switch (n) {
		case 1: return Engine::filterModel_transLadder;
		case 2: return Engine::filterModel_diodeLadder;
		case 3: return Engine::filterModel_ota;
		
		case 0:
		default:
			return Engine::filterModel_none;
		}
	}

	// returns amount to oversample by
	static size_t DetermineUpsampling(
		double nativeSampleRate,
		juce::ScopedPointer<Utils::IResampler>& pResampler /*inOut*/)
	{
		// TODO: add quality setting that will change the behavior of this

		DEBUG_ASSERT(nativeSampleRate > 0.f);

		uint32_t roundedSampleRate = Utils::RoundTo<uint32_t>(nativeSampleRate);

		if (roundedSampleRate < 44100) {

			// Sample rate < 44.1
			// Use 44.1k resampler

			LOG(juce::String::formatted("Low sample rate %f, using 44.1 kHz resampling filter", nativeSampleRate));
			roundedSampleRate = 44100;
		}
		else if (roundedSampleRate > 100000) {
			
			// Sample rate > 100k
			// i.e. 176.4 kHz, 192 kHz
			// (but would also catch any weird-but-high-enough sample rate)
			// no need to oversample
			
			pResampler = nullptr;
			return 1;
		}

		switch (roundedSampleRate) {
		
		// 44.1 kHz-based
		case 44100:
			pResampler = new Utils::IirDownsampler_176_44;
			return 4;
		case 88200:
			pResampler = new Utils::IirDownsampler_176_88;
			return 2;

		// 48 kHz-based
		case 48000:
			pResampler = new Utils::IirDownsampler_192_48;
			return 4;
		case 96000:
			pResampler = new Utils::IirDownsampler_192_96;
			return 2;
			
		// Unusual sample rate
		default:
			LOG(juce::String::formatted("Not oversampling due to unusual sample rate %f", nativeSampleRate));
			pResampler = nullptr;
			return 1;
		}
	}
}

// TODO: randomize initial phase via Oscillator constructor arg
SynthEngine::SynthEngine() :
	m_lastNote(60)
{}

SynthEngine::~SynthEngine() {}

std::vector<Param*> const& SynthEngine::GetParamList() const {
	return m_params.GetParamList();
}

void SynthEngine::PrepareToPlay(double sampleRate, int samplesPerBlock) {

	LOG(juce::String::formatted("PrepareToPlay(%f, %i)" , sampleRate , samplesPerBlock));

	m_sampleRateNative = sampleRate;
	m_nOversample = Detail::DetermineUpsampling(sampleRate, m_pResampler);
	m_sampleRateOver = sampleRate * double(m_nOversample);

	if (m_pResampler) m_pResampler->Clear();

	m_pitchProc.PrepareToPlay(m_sampleRateOver, samplesPerBlock);
	m_filtEnv.PrepareToPlay(m_sampleRateOver, samplesPerBlock);
	m_osc1.PrepareToPlay(m_sampleRateOver, samplesPerBlock);
	m_osc2.PrepareToPlay(m_sampleRateOver, samplesPerBlock);
	m_subOsc.PrepareToPlay(m_sampleRateOver, samplesPerBlock);
	m_filter.PrepareToPlay(m_sampleRateOver, samplesPerBlock);
	m_vca.PrepareToPlay(m_sampleRateOver, samplesPerBlock);

	m_filtFreqCvFilt.SetFreq(Engine::k_filtCvCutoff_Hz / m_sampleRateOver);
}

void SynthEngine::Process(juce::AudioSampleBuffer& juceBuf, juce::MidiBuffer& midiMessages) {
	
	juce::FloatVectorOperations::enableFlushToZeroMode(true);

	size_t nSampNative = juceBuf.getNumSamples();
	size_t nSampOver = nSampNative * m_nOversample;
	size_t nChan = juceBuf.getNumChannels();

	// Oversampled buf
	Buffer overBuf(nSampOver);

	// Get params
	// TODO: get actual values for all of these
	float osc2Tuning = float(m_params.osc2coarse->GetInt()) + m_params.osc2fine->GetActualValue();
	float outputVol = 1.0f;
	uint32_t pitchBendAmt = 12;
	bool bVcaEnv = m_params.vcaSource->GetInt();

	{
		float attVal = m_params.envAtt->getValue();
		float decVal = m_params.envDec->getValue();
		float susVal = m_params.envSus->getValue();
		float relVal = m_params.envRel->getValue();
		
		DEBUG_ASSERT(attVal >= 0.0 && attVal <= 1.0);
		DEBUG_ASSERT(decVal >= 0.0 && decVal <= 1.0);
		DEBUG_ASSERT(relVal >= 0.0 && relVal <= 1.0);

		// Times in seconds (log-interp 1ms to 4s)
		double attTime = Utils::LogInterp<double>(0.001, 4.0, attVal);
		double decTime = Utils::LogInterp<double>(0.001, 4.0, decVal);
		double relTime = Utils::LogInterp<double>(0.001, 4.0, relVal);

		m_filtEnv.SetVals(attTime, decTime, susVal, relTime);
	}

	// Process:
	// 1. MIDI
	// 2. Mod sources (Env/LFO)
	// 3. Pitch
	// 4. Oscillators & Mixer
	// 5. Filter
	// 6. Overdrive
	// 7. VCA
	// 8. Effects
	// 9. Output Volume

	eventBuf_t<gateEvent_t> gateEvents;
	eventBuf_t<uint8_t> noteEvents;
	eventBuf_t<uint8_t> velEvents;
	eventBuf_t<uint16_t> pitchBendEvents;

	// 1. MIDI
	m_midiProc.Process(nSampOver, m_nOversample, midiMessages, gateEvents, noteEvents, velEvents, pitchBendEvents);

	// 2. Envelope & LFO
	Buffer filtEnvBuf(nSampOver);
	m_filtEnv.Process(gateEvents, filtEnvBuf);

#if 0 // TODO
	Buffer lfo1(nSamp);
	Buffer lfo2(nSamp);
#endif

	// 3. Pitch

	Buffer freqPhaseBuf1(nSampOver);
	
	m_lastNote = Utils::EventBufToBuf<uint8_t, float>(m_lastNote, noteEvents, nSampOver, freqPhaseBuf1.Get());
	
	m_pitchProc.ProcessPitchBend(freqPhaseBuf1, pitchBendEvents, pitchBendAmt);

	// TODO: mod

	// VCO tuning instability
	// TODO:
	// - Normal (Gaussian) distribution
	// - Consistent rate independent of buffer size
	// - Lowpass
	freqPhaseBuf1 += ((m_random.nextFloat() - 0.5f) * 2.0f*Engine::k_vcoRandPitchAmt);
	osc2Tuning += ((m_random.nextFloat() - 0.5f) * 2.0f*Engine::k_vcoRandPitchAmt);

	Buffer freqPhaseBuf2(freqPhaseBuf1);
	freqPhaseBuf2 += osc2Tuning;

	// Pitch to freq
	m_pitchProc.PitchToFreq(freqPhaseBuf1);
	m_pitchProc.PitchToFreq(freqPhaseBuf2);

	// 4. Oscillators & Mixer
	ProcessOscsAndMixer_(overBuf, freqPhaseBuf1, freqPhaseBuf2);

	// 5. Filter
	ProcessFilter_(overBuf, filtEnvBuf);

	// 6. Overdrive
	// TODO

	// 7. VCA
	m_vca.Process(overBuf, gateEvents, filtEnvBuf, bVcaEnv);

	// Downsample to native sample rate
	// Technically we could do this before VCA, but the envelope is at oversampled rate
	
	if (m_nOversample <= 1)
	{
		DEBUG_ASSERT(overBuf.GetLength() == nSampNative);

		// Copy buffer to output buffer (for all channels)
		for (size_t chan = 0; chan < nChan; ++chan) {
			juce::FloatVectorOperations::copy(juceBuf.getWritePointer(chan), overBuf.Get(), nSampNative);
		}
	}
	else
	{
		// Can downsample staight into Juce buffer
		Buffer buf(juceBuf.getWritePointer(0), nSampNative);

		DEBUG_ASSERT(Utils::ApproxEqual(m_sampleRateNative*m_nOversample, m_sampleRateOver));
		DEBUG_ASSERT(m_pResampler);

		m_pResampler->Process(buf, overBuf);

		// Copy buffer to output buffer (for channels > 0)
		for (size_t chan = 1; chan < nChan; ++chan) {
			juce::FloatVectorOperations::copy(juceBuf.getWritePointer(chan), buf.Get(), nSampNative);
		}
	}
	
	// 8. Effects
	// TODO

	// 9. Output Volume
	for (size_t chan = 0; chan < nChan; ++chan) {
		juce::FloatVectorOperations::multiply(juceBuf.getWritePointer(chan), juceBuf.getReadPointer(0), outputVol, nSampNative);
	}
	
}

void SynthEngine::ProcessOscsAndMixer_(Buffer& mainBuf /*out*/, Buffer& freqPhaseBuf1 /*inout*/, Buffer& freqPhaseBuf2 /*inout*/)
{
	size_t const nSamp = mainBuf.GetLength();
	mainBuf.Clear();

	// Get params
	float osc1Gain = m_params.mixOsc1->GetActualValue();
	float osc2Gain = m_params.mixOsc2->GetActualValue();
	float subGain = m_params.mixSub->GetActualValue();
	float ringGain = m_params.mixRing->GetActualValue();
	float noiseGain = m_params.mixNoise->GetActualValue();

	float osc1shape = m_params.osc1shape->GetActualValue();
	float osc2shape = m_params.osc2shape->GetActualValue();
	int subOscOct = m_params.subOscOct->GetInt();

	float preFiltGain = m_params.filtGain->GetActualValue();

	bool bProcOsc1Sig = (osc1Gain > 0.0f || ringGain > 0.0f);
	bool bProcOsc1Phase = (bProcOsc1Sig || subGain > 0.0f);

	bool bProcOsc2Sig = (osc2Gain > 0.0f || ringGain > 0.0f);
	bool bProcOsc2Phase = bProcOsc2Sig;

	// DEBUG (you know what they say about premature optimization...)
	bProcOsc1Sig = bProcOsc1Phase = bProcOsc2Sig = bProcOsc2Phase = true;

	// Wave shapes
	Engine::waveform_t osc1wave = Detail::MainOscToWave(m_params.osc1wave->GetInt());
	Engine::waveform_t osc2wave = Detail::MainOscToWave(m_params.osc2wave->GetInt());
	Engine::waveform_t subOscWave = Detail::SubOscToWave(m_params.subOscWave->GetInt());

	// Allocate memory

	Buffer osc1Buf(nSamp);
	Buffer osc2Buf(nSamp);

	// Process oscs

	if (bProcOsc1Sig) {
		DEBUG_ASSERT(bProcOsc1Phase);

		m_osc1.ProcessFromFreq(osc1Buf, freqPhaseBuf1, osc1wave, osc1shape);

		if (osc1Gain > 0.0f) {
			Buffer tempOscBuf(osc1Buf, osc1Gain);
			mainBuf += tempOscBuf;
		}
	}

	if (bProcOsc2Sig) {
		DEBUG_ASSERT(bProcOsc2Phase);

		m_osc2.ProcessFromFreq(osc2Buf, freqPhaseBuf2, osc2wave, osc2shape);

		if (osc2Gain > 0.0f) {
			Buffer tempOscBuf(osc2Buf, osc2Gain);
			mainBuf += tempOscBuf;
		}
	}

	// This is the last we need to use osc2Buf, so can use it for ring mod
	if (ringGain > 0.0f) {
		osc2Buf *= osc1Buf;
		osc2Buf *= ringGain;
		mainBuf += osc2Buf;
	}

	// At this point we're done with the contents of osc1Buf and osc2Buf - can use freely
	if (subGain > 0.0f) {
		m_subOsc.ProcessSub(osc1Buf, freqPhaseBuf1, subOscWave, subOscOct);
		osc1Buf *= subGain;
		mainBuf += osc1Buf;
	}

	/*
	if (noiseGain > 0.0f) {
		// TODO: process (noise -> osc2Buf)
		osc2Buf *= noiseGain;
		mainBuf += osc2Buf;
	}
	*/

	if (!Utils::ApproxEqual(preFiltGain, 1.0f)) {
		mainBuf *= preFiltGain;
	}
}

void SynthEngine::ProcessFilter_(Buffer& buf, Buffer const& envBuf)
{
	float filtRes = m_params.filtRes->getValue();

	Engine::filterModel_t filtModel = Detail::ConvertFiltModel(m_params.filtModel->GetInt());

	// Convert semitones to actual 0-1 range
	// range = 20-20000 = 1000x = 9.966 octaves (then x12 semitones)
	float filtCutoffRandAmt_01 = Engine::k_filtCutoffRandAmt_semi / (9.966f * 12.0f);
	float cutoffRand = ((m_random.nextFloat() - 0.5f) * 2.0f * filtCutoffRandAmt_01);

	sample_t filtCutoff_01 = m_params.filtFreq->getValue() + cutoffRand;
	//sample_t filtCutoff = Utils::LogInterp<double>(20.0, 20000.0, filtCutoff_01) / m_sampleRateOver;

	float filtEnvAmt = m_params.filtEnv->GetActualValue();
	
	// TODO: apply curve to filtEnvAmt

	//Buffer filtCv(filtCutoff, nSamp);
	Buffer filtCv(envBuf);
	filtCv *= filtEnvAmt;
	filtCv += filtCutoff_01;
	
	// TODO: LFO, velocity, kb tracking

	// TODO: test accuracty, possibly use exact log interp when KB tracking with high resonance
	Utils::FastLogInterp(20.0f, 20000.0f, filtCv);
	filtCv /= m_sampleRateOver;

	m_filtFreqCvFilt.ProcessLowpass(filtCv);
	m_filter.Process(buf, filtCv, filtRes, filtModel);
}