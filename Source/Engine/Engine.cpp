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

using namespace Engine;

const double k_filtCvCutoff_Hz = 100.0;
float k_vcoRandPitchAmt = 0.01f; // In semitones
float k_filtCutoffRandAmt_semi = 0.05f; // In semitones

namespace Detail {
	static waveform_t MainOscToWave(size_t n) {
		switch (n) { // tri/rect/saw
		case 0: return waveShape_tri; break;
		case 1: return waveShape_pwm; break;
		case 2: return waveShape_saw; break;
		default:
			LOG(juce::String::formatted("MainOscToWave, unknown wave %u", n));
			DEBUG_ASSERT(false);
			return waveShape_saw;
		}
	}

	static waveform_t SubOscToWave(size_t n) {
		switch (n) { // tri/squ/pulse
		case 0: return waveShape_tri;
		case 1: return waveShape_squ50;
		case 2: return waveShape_pulse25;
		default:
			LOG(juce::String::formatted("SubOscToWave, unknown wave %u", n));
			DEBUG_ASSERT(false);
			return waveShape_tri;
		}
	}

	static waveform_t Mod1ToWave(size_t n) {
		switch (n) {
		case 0: return waveShape_tri;
		case 1: return waveShape_sin;
		case 2: return waveShape_squ50;
		case 3: return waveShape_saw;
		case 4: return waveShape_sawDown;
		default:
			LOG(juce::String::formatted("Mod1ToWave, unknown wave %u", n));
			DEBUG_ASSERT(false);
			return waveShape_sin;
		}
	}

	static waveform_t Mod2ToWave(size_t n) {
		switch (n) {
		case 0: return waveShape_envelopeDown;
		case 1: return waveShape_envelope;
		case 2: return waveShape_envelopeLooped;
		default:
			LOG(juce::String::formatted("Mod2ToWave, unknown wave %u", n));
			DEBUG_ASSERT(false);
			return waveShape_envelope;
		}
	}

	static filterModel_t ConvertFiltModel(size_t n)
	{
		switch (n) {
		case 0: return filterModel_none;
		case 1: return filterModel_transLadder;
		case 2: return filterModel_diodeLadder;
		default:
			LOG(juce::String::formatted("ConvertFiltModel, unknown model %u", n));
			DEBUG_ASSERT(false);
			return filterModel_none;
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

	// val: 0-1
	// returns time in seconds (range 1ms to 4s)
	static double EnvValToTime(double val) {
		// Times in seconds (range 1ms to 4s)
		double time = 4.0 * (val*val);
		time = std::max(time, 0.001);
		return time;
	}
}

SynthEngine::SynthEngine() :
	m_lastNote(60)
{
	m_rBufs.push_back(m_mainBuf);
	m_rBufs.push_back(m_adsrBuf);
	m_rBufs.push_back(m_mod1Buf);
	m_rBufs.push_back(m_mod2Buf);
	m_rBufs.push_back(m_freqPhaseBuf1);
	m_rBufs.push_back(m_freqPhaseBuf2);
	m_rBufs.push_back(m_filtCv);
}

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
	
	m_mod1.PrepareToPlay(m_sampleRateOver, samplesPerBlock);
	m_mod2.PrepareToPlay(m_sampleRateOver, samplesPerBlock);
	
	m_oscs.PrepareToPlay(m_sampleRateOver, samplesPerBlock);
	m_filter.PrepareToPlay(m_sampleRateOver, samplesPerBlock);
	m_vca.PrepareToPlay(m_sampleRateOver, samplesPerBlock);

	m_filtFreqCvFilt.SetFreq(k_filtCvCutoff_Hz / m_sampleRateOver);

	ReallocBufs_(samplesPerBlock);
}

void SynthEngine::ReallocBufs_(size_t nSamp) {
	
	size_t const currLen = m_mainBuf.GetLength();
	size_t const currAllocLen = m_mainBuf.GetAllocLength();

	for (auto it = m_rBufs.begin(); it != m_rBufs.end(); ++it) {
		DEBUG_ASSERT(it->get().GetLength() == currLen);
		DEBUG_ASSERT(it->get().GetAllocLength() == currAllocLen);
	}

	if (nSamp != currLen || nSamp != currAllocLen) {
		for (auto it = m_rBufs.begin(); it != m_rBufs.end(); ++it) {
			it->get().Resize(nSamp, true);
		}
	}
}

void SynthEngine::ResizeBufsNoRealloc_(size_t nSamp) {

	size_t const currLen = m_mainBuf.GetLength();
	size_t const currAllocLen = m_mainBuf.GetAllocLength();

	for (auto it = m_rBufs.begin(); it != m_rBufs.end(); ++it) {
		DEBUG_ASSERT(it->get().GetLength() == currLen);
		DEBUG_ASSERT(it->get().GetAllocLength() == currAllocLen);
	}

	// If already the right size, no need to do anything
	if (nSamp != currLen) {

		if (nSamp > currAllocLen) {
			LOG(juce::String::formatted(
				"WARNING: Unexpected buffer size increase, was %u, now %u - reallocating from audio thread!",
				currLen, nSamp));
		}

		for (auto it = m_rBufs.begin(); it != m_rBufs.end(); ++it) {
			it->get().Resize(nSamp, false);
		}
	}
}

void SynthEngine::Process(juce::AudioSampleBuffer& juceBuf, juce::MidiBuffer& midiMessages) {
	
	juce::FloatVectorOperations::enableFlushToZeroMode(true);

	size_t nSampNative = juceBuf.getNumSamples();
	size_t nSampOver = nSampNative * m_nOversample;
	size_t nChan = juceBuf.getNumChannels();

	ResizeBufsNoRealloc_(nSampOver);

	// Get params
	float osc2Tuning = m_params.osc2coarse->GetActualValue() + m_params.osc2fine->GetActualValue() + 12.0f*float(m_params.osc2oct->GetInt());
	float outputVol = 1.0f;
	uint32_t pitchBendAmt = 12;
	bool bVcaEnv = (m_params.vcaSource->GetInt() == 2);
	bool bVcaClick = (m_params.vcaSource->GetInt() == 0);

	{
		double attVal, decVal, susVal, relVal;

		attVal = m_params.envAtt->getValue();
		decVal = m_params.envDec->getValue();
		susVal = m_params.envSus->getValue();
		relVal = m_params.envRel->getValue();
		
		DEBUG_ASSERT(attVal >= 0.0 && attVal <= 1.0);
		DEBUG_ASSERT(decVal >= 0.0 && decVal <= 1.0);
		DEBUG_ASSERT(relVal >= 0.0 && relVal <= 1.0);

		m_filtEnv.SetVals(
			Detail::EnvValToTime(attVal),
			Detail::EnvValToTime(decVal),
			susVal,
			Detail::EnvValToTime(relVal));
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

	// TODO: need to do something about these - they alloc during callback
	eventBuf_t<gateEvent_t> gateEvents;
	eventBuf_t<uint8_t> noteEvents;
	eventBuf_t<uint8_t> velEvents;
	eventBuf_t<uint16_t> pitchBendEvents;

	// 1. MIDI
	m_midiProc.Process(nSampOver, m_nOversample, midiMessages, gateEvents, noteEvents, velEvents, pitchBendEvents);

	// 2. Envelope & LFO
	m_filtEnv.Process(gateEvents, m_adsrBuf);

	ProcessMod_(gateEvents, m_mod1Buf, m_mod2Buf);

	// 3. Pitch

	m_lastNote = Utils::EventBufToBuf<uint8_t, float>(m_lastNote, noteEvents, nSampOver, m_freqPhaseBuf1.Get());
	
	m_pitchProc.ProcessPitchBend(m_freqPhaseBuf1, pitchBendEvents, pitchBendAmt);

	// TODO: pitch mod

	// VCO tuning instability
	// TODO:
	// - Normal (Gaussian) distribution
	// - Consistent rate independent of buffer size
	// - Lowpass
	m_freqPhaseBuf1 += ((m_random.nextFloat() - 0.5f) * 2.0f*k_vcoRandPitchAmt);
	osc2Tuning += ((m_random.nextFloat() - 0.5f) * 2.0f*k_vcoRandPitchAmt);

	m_freqPhaseBuf2 = m_freqPhaseBuf1;
	m_freqPhaseBuf2 += osc2Tuning;

	// Pitch to freq
	m_pitchProc.PitchToFreq(m_freqPhaseBuf1);
	m_pitchProc.PitchToFreq(m_freqPhaseBuf2);

	// 4. Oscillators & Mixer
	ProcessOscsAndMixer_(m_mainBuf, m_freqPhaseBuf1, m_freqPhaseBuf2);

	// 5. Filter
	ProcessFilter_(m_mainBuf, m_adsrBuf, m_mod1Buf, m_mod2Buf);

	// 6. Overdrive
	// TODO

	// 7. VCA
	m_vca.Process(m_mainBuf, gateEvents, m_adsrBuf, bVcaEnv, bVcaClick);

	// Downsample to native sample rate
	// Technically we could do this before VCA, but the envelope is at oversampled rate
	DownsampleAndCopyToStereo_(m_mainBuf, juceBuf);
	
	// 8. Effects
	// TODO

	// 9. Output Volume
	for (size_t chan = 0; chan < nChan; ++chan) {
		juce::FloatVectorOperations::multiply(juceBuf.getWritePointer(chan), juceBuf.getReadPointer(0), outputVol, nSampNative);
	}
}

void SynthEngine::ProcessMod_(
	eventBuf_t<gateEvent_t> const& gateEvents /*in*/,
	Buffer& mod1Buf /*out*/,
	Buffer& mod2Buf /*out*/)
{
	// TODO: LFO1 high freq range & KB tracking
	float mod1shape = m_params.mod1shape->GetActualValue();
	waveform_t mod2wave = Detail::Mod2ToWave(m_params.mod2type->GetInt());

	bool blfo1KbTrack = (m_params.mod1range->GetInt() == 2);
	bool blfo1HighFreq = IsMod1HighFreq_();

	sample_t mod2attack = m_params.mod2attack->getValue();
	sample_t mod2decay = m_params.mod2decay->getValue();

	sample_t lfo1freq = sample_t(
		blfo1HighFreq ?
		Utils::LogInterp<double>(20., 1000., m_params.mod1freq->getValue()) / m_sampleRateOver :
		Utils::LogInterp<double>(0.1, 20., m_params.mod1freq->getValue()) / m_sampleRateOver );

	// Not used if mod2wave is envelope
	sample_t lfo2freq = sample_t(
		Utils::LogInterp<double>(0.1, 20., mod2attack) / m_sampleRateOver);

	if (blfo1KbTrack) {
		mod1Buf.Clear();
		// TODO: put keyboard tracking data into mod1Buf
		m_mod1.ProcessHighFreqWithKbTracking(gateEvents, mod1shape, lfo1freq, mod1Buf);
	}
	else if (blfo1HighFreq) {
		m_mod1.ProcessHighFreq(gateEvents, mod1shape, lfo1freq, mod1Buf);
	}
	else {
		m_mod1.ProcessLowFreq(gateEvents, mod1shape, lfo1freq, mod1Buf);
	}

	// TODO: only pass in gateEvents if LFO reset enabled (otherwise pass in empty vector)

	bool bLooped = (mod2wave == waveShape_envelopeLooped);

	double mod2AttTime = Detail::EnvValToTime(mod2attack);
	double mod2DecTime = Detail::EnvValToTime(mod2decay);
	m_mod2.SetVals(mod2AttTime, mod2DecTime, bLooped);
	m_mod2.Process(gateEvents, mod2Buf);

	switch (mod2wave) {
	case waveShape_envelopeDown:
		mod2Buf *= -1.0f;
		break;
	case waveShape_envelopeLooped:
		mod2Buf -= 0.5f;
		mod2Buf *= 2.0f;
		break;
	case waveShape_envelope:
		break;
	default:
		// TODO: error
		break;
	}
}

void SynthEngine::ProcessOscsAndMixer_(Buffer& mainBuf /*out*/, Buffer& freqPhaseBuf1 /*inout*/, Buffer& freqPhaseBuf2 /*inout*/)
{
	mainBuf.Clear();

	Oscillators::Params oscParams;

	// Get params
	oscParams.osc1Gain = m_params.mixOsc1->GetActualValue();
	oscParams.osc2Gain = m_params.mixOsc2->GetActualValue();
	oscParams.subGain = m_params.mixSub->GetActualValue();
	oscParams.ringGain = m_params.mixRing->GetActualValue();
	float noiseGain = m_params.mixNoise->GetActualValue();

	oscParams.osc1Shape = m_params.osc1shape->GetActualValue();
	oscParams.subOscOct = m_params.subOscOct->GetInt();

	oscParams.bSync = m_params.osc2sync->GetBool();

	// Wave shapes
	oscParams.osc1Wave = Detail::MainOscToWave(m_params.osc1wave->GetInt());
	oscParams.osc2Wave = Detail::MainOscToWave(m_params.osc2wave->GetInt());
	oscParams.subOscWave = Detail::SubOscToWave(m_params.subOscWave->GetInt());

	m_oscs.Process(mainBuf, freqPhaseBuf1, freqPhaseBuf2, oscParams);
	
	// TODO: noise
#if 0
	if (noiseGain > 0.0f) {
		// TODO: process (noise -> osc2Buf)
		osc2Buf *= noiseGain;
		mainBuf += osc2Buf;
	}
#endif
}

void SynthEngine::ProcessFilter_(
	Buffer& buf /*inOut*/,
	Buffer const& envBuf,
	Buffer const& filtMod1Buf,
	Buffer const& filtMod2Buf)
{
	size_t const nSamp = buf.GetLength();

	// TODO: velocity, kb tracking

	// Basic params
	float filtRes;
	filterModel_t filtModel;
	uint8_t nPoles;
	sample_t filtCutoff_01;
	{
		filtRes = m_params.filtRes->getValue();

		filtModel = Detail::ConvertFiltModel(m_params.filtModel->GetInt());

		nPoles = (m_params.filtPoles->GetInt() ? 4 : 2);

		// Convert semitones to actual 0-1 range
		// range = 20-20000 = 1000x = 9.966 octaves (then x12 semitones)
		float filtCutoffRandAmt_01 = k_filtCutoffRandAmt_semi / (9.966f * 12.0f);
		float cutoffRand = ((m_random.nextFloat() - 0.5f) * 2.0f * filtCutoffRandAmt_01);

		filtCutoff_01 = m_params.filtFreq->getValue() + cutoffRand;
	}

	// Mod & env amts
	bool bEnv, bMod1, bMod2;
	bool bMod1HighFreq;
	float filtEnvAmt, filtMod1Amt, filtMod2Amt;
	{
		filtEnvAmt = m_params.filtEnv->GetActualValue();

		bEnv = !Utils::ApproxEqual(filtEnvAmt, 0.0f, 0.005f);

		filtMod1Amt = m_params.filtMod1Amt->GetActualValue();
		filtMod2Amt = m_params.filtMod2Amt->GetActualValue();

		bMod1 = !Utils::ApproxEqual(filtMod1Amt, 0.0f, 0.005f);
		bMod2 = !Utils::ApproxEqual(filtMod2Amt, 0.0f, 0.005f);

		// Apply curve (x^2) to LFO amt
		filtMod1Amt *= filtMod1Amt;
		filtMod2Amt *= filtMod2Amt;

		bMod1HighFreq = bMod1 && IsMod1HighFreq_();
	}

	// Pre- & post-filter gain values
	sample_t preFiltGain, postFiltGain;
	{
		/*
		Simple gain knob would cause overall volume change (obviously).
		So we add post-filter gain in order to make gain knob roughly volume-neutral.

		If we just made post-gain 1/pre, then we would actually lose volume at the
		top of the knob, as clipping starts to reduce the volume. That's even worse
		because it's the opposite of what the user might expect. So we have to be
		smarter with what we make the post-gain.

		It's impossible to calculate exactly how to set the post-gain for perfect
		volume-neutral behavior, since not only does it depend on freq and resonance,
		but also on the waveform going into the filter.

		Empirically, adding 0.25 overall seems to make it roughly linear, and since
		it's added uniformly across the whole range it won't cause any weird
		discontinuous behavior.
		*/
		preFiltGain = m_params.filtGain->GetActualValue();
		preFiltGain = preFiltGain*preFiltGain*preFiltGain;
		preFiltGain = Utils::Interp(0.1f, 8.0f, preFiltGain);

		postFiltGain = 1.f / preFiltGain + 0.25f;
	}

	m_filtCv.Set(filtCutoff_01);
	if (bEnv) {
		m_filtCv.AddWithMultiply(envBuf, filtEnvAmt);
	}

	if (bMod2) {
		m_filtCv.AddWithMultiply(filtMod2Buf, filtMod2Amt);
	}

	if (bMod1 && bMod1HighFreq) {
		// If high freq, add mod1 *after* CV lowpass filter
		// TODO: if high freq, then we probably want this to be linear FM, not log?
		m_filtFreqCvFilt.ProcessLowpass(m_filtCv);
		m_filtCv.AddWithMultiply(filtMod1Buf, filtMod1Amt);
	}
	else if (bMod1) {
		m_filtCv.AddWithMultiply(filtMod1Buf, filtMod1Amt);
		m_filtFreqCvFilt.ProcessLowpass(m_filtCv);
	}
	else {
		m_filtFreqCvFilt.ProcessLowpass(m_filtCv);
	}

	// TODO: test accuracy, possibly use exact log interp when KB tracking with high resonance
	// NOTE: at this point, filtCv can exceed range [0,1]. This is acceptable.
	Utils::FastLogInterp(20.0f, 20000.0f, m_filtCv);
	m_filtCv /= m_sampleRateOver;

	// Do the processing!

	buf *= preFiltGain;
	m_filter.Process(buf, m_filtCv, filtRes, filtModel, nPoles);
	buf *= postFiltGain;
}

void SynthEngine::DownsampleAndCopyToStereo_(
	Buffer const& overBuf /*in*/,
	juce::AudioSampleBuffer& juceBuf /*out*/) const
{
	size_t nChan = juceBuf.getNumChannels();
	size_t nSampNative = juceBuf.getNumSamples();

	if (m_nOversample <= 1)
	{
		DEBUG_ASSERT(overBuf.GetLength() == nSampNative);

		// Copy buffer to output buffer (for all channels)
		for (size_t chan = 0; chan < nChan; ++chan) {
			juce::FloatVectorOperations::copy(juceBuf.getWritePointer(chan), overBuf.GetConst(), nSampNative);
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
}

bool SynthEngine::IsMod1HighFreq_() const {
	return (m_params.mod1range->GetInt() != 0);
}
