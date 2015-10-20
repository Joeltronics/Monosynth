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

#define DONT_REUSE_JUCE_BUF 1

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
	m_sampleRate = sampleRate;
	m_pitchProc.PrepareToPlay(sampleRate, samplesPerBlock);
	m_filtEnv.PrepareToPlay(sampleRate, samplesPerBlock);
	m_osc1.PrepareToPlay(sampleRate, samplesPerBlock);
	m_osc2.PrepareToPlay(sampleRate, samplesPerBlock);
	m_subOsc.PrepareToPlay(sampleRate, samplesPerBlock);
	m_vca.PrepareToPlay(sampleRate, samplesPerBlock);
}

void SynthEngine::Process(juce::AudioSampleBuffer& juceBuf, juce::MidiBuffer& midiMessages) {
	
	juce::FloatVectorOperations::enableFlushToZeroMode(true);

	size_t nSamp = juceBuf.getNumSamples();
	size_t nChan = juceBuf.getNumChannels();

#ifdef DONT_REUSE_JUCE_BUF
	Buffer buf(nSamp);
#else
	Buffer buf(juceBuf.getWritePointer(0), nSamp);
#endif

	// Get params
	// TODO: get actual values
	float osc2Tuning = float(m_params.osc2coarse->GetInt()) + m_params.osc2fine->GetActualValue();

	float outputVol = 1.0f;

	uint32_t pitchBendAmt = 12;

	float vcoRandPitchAmt = 0.01f; // In semitones

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
	m_midiProc.Process(nSamp, midiMessages, gateEvents, noteEvents, velEvents, pitchBendEvents);

	// 2. Envelope & LFO

#if 0 // TODO
	Buffer filtEnvBuf(nSamp);
	m_filtEnv.Process(gateEvents, filtEnvBuf);

	Buffer lfo1(nSamp);
	Buffer lfo2(nSamp);
#endif

	// 3. Pitch

	Buffer freqPhaseBuf1(nSamp);
	
	m_lastNote = Utils::EventBufToBuf<uint8_t, float>(m_lastNote, noteEvents, nSamp, freqPhaseBuf1.Get());
	
	m_pitchProc.ProcessPitchBend(freqPhaseBuf1, pitchBendEvents, pitchBendAmt);

	// TODO: mod

	// VCO tuning instability
	// TODO:
	// - Normal (Gaussian) distribution
	// - Consistent rate independent of buffer size
	// - Lowpass
	freqPhaseBuf1 += ((m_random.nextFloat() - 0.5f) * 2.0f*vcoRandPitchAmt);
	osc2Tuning += ((m_random.nextFloat() - 0.5f) * 2.0f*vcoRandPitchAmt);

	Buffer freqPhaseBuf2(freqPhaseBuf1);
	freqPhaseBuf2 += osc2Tuning;

	// Pitch to freq
	m_pitchProc.PitchToFreq(freqPhaseBuf1);
	m_pitchProc.PitchToFreq(freqPhaseBuf2);

	// 4. Oscillators & Mixer
	ProcessOscsAndMixer_(buf, freqPhaseBuf1, freqPhaseBuf2);

	// 5. Filter
	// TODO

	// 6. Overdrive
	// TODO

	// 7. VCA
	m_vca.Process(buf, gateEvents);
	
#ifdef DONT_REUSE_JUCE_BUF
	// Copy buffer to output buffer (for all channels)
	for (size_t chan = 0; chan < nChan; ++chan) {
		juce::FloatVectorOperations::copy(juceBuf.getWritePointer(chan), buf.Get(), nSamp);
	}
#else
	// If not mono, copy channel 0 to all others
	for (size_t chan = 1; chan < nChan; ++chan) {
		juce::FloatVectorOperations::copy(juceBuf.getWritePointer(chan), juceBuf.getReadPointer(0), nSamp);
	}
#endif
	
	// 8. Effects
	// TODO

	// 9. Output Volume
	for (size_t chan = 0; chan < nChan; ++chan) {
		juce::FloatVectorOperations::multiply(juceBuf.getWritePointer(chan), juceBuf.getReadPointer(0), outputVol, nSamp);
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
