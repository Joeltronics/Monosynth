/*
  ==============================================================================

    Engine.cpp
    Created: 7 Sep 2015 12:30:58pm
    Author:  Joel

  ==============================================================================
*/

#include "Engine.h"

#include "JuceHeader.h"

#include "Types.h"

#include "Utils/ApproxEqual.h"
#include "Utils/DspUtils.h"

#define DONT_REUSE_JUCE_BUF 1

// TODO: randomize initial phase
SynthEngine::SynthEngine() :
	m_lastNote(60),
	m_prevPhaseOsc1(0.0f),
	m_prevPhaseOsc2(0.0f)
{}
SynthEngine::~SynthEngine() {}

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
	float osc2Tuning = 12.01f;

	float outputVol = 1.0f;

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
	eventBuf_t<int> pitchBendEvents;

	// 1. MIDI
	m_midiProc.Process(nSamp, midiMessages, gateEvents, noteEvents, velEvents, pitchBendEvents);

	// 2a. Envelopes

	// TODO: only need to process this if enabled for VCA
	// (though I guess it doesn't use that much processor or memory, so maybe it's fine)
	Buffer ampEnvBuf(nSamp);
	m_ampEnv.Process(gateEvents, ampEnvBuf);

#if 0 // TODO
	Buffer filtEnvBuf(nSamp);
	m_filtEnv.Process(gateEvents, filtEnvBuf);
#endif

	// 2b. LFO

#if 0 // TODO
	Buffer lfo1(nSamp);
	Buffer lfo2(nSamp);
#endif

	// 3. Pitch

	Buffer freqPhaseBuf1(nSamp);
	
	m_lastNote = Utils::EventBufToBuf<uint8_t, float>(m_lastNote, noteEvents, nSamp, freqPhaseBuf1.Get());
	
	// TODO: bend

	// TODO: mod

	Buffer freqPhaseBuf2(freqPhaseBuf1);
	freqPhaseBuf2 += osc2Tuning;

	// TODO: tuning instability


	if (!gateEvents.empty()) {
		__nop();
		__nop();
		__nop();
	}


	// Pitch to freq
	m_pitchProc.PitchToFreq(freqPhaseBuf1);
	m_pitchProc.PitchToFreq(freqPhaseBuf2);



	if (!gateEvents.empty()) {
		__nop();
		__nop();
		__nop();
	}




	// 4. Oscillators & Mixer
	ProcessOscsAndMixer_(buf, freqPhaseBuf1, freqPhaseBuf2);

	// 5. Filter
	// TODO

	// 6. Overdrive
	// TODO

	// 7. VCA
	
	// TODO: more features
	buf *= ampEnvBuf;











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

void SynthEngine::PrepareToPlay(double sampleRate, int samplesPerBlock) {
	m_sampleRate = sampleRate;
	m_pitchProc.PrepareToPlay(sampleRate, samplesPerBlock);
	m_ampEnv.PrepareToPlay(sampleRate, samplesPerBlock);
	m_filtEnv.PrepareToPlay(sampleRate, samplesPerBlock);
}

void SynthEngine::ProcessOscsAndMixer_(Buffer& MainBuf, Buffer& FreqPhaseBuf1, Buffer& FreqPhaseBuf2)
{
	size_t const nSamp = MainBuf.GetLength();
	MainBuf.Clear();

	// TODO: do we really need to preallocate memory here?
	Buffer osc1Buf(nSamp);
	Buffer osc2Buf(nSamp);

	// Get params
	// TODO: get actual values
	float osc1Gain = 0.5f;
	float osc2Gain = 0.0f;
	float subGain = 0.0f;
	float ringGain = 0.0f;
	float noiseGain = 0.0f;

	float preFiltGain = 1.0f;

	bool bProcOsc1Sig = (osc1Gain > 0.0f || ringGain > 0.0f);
	bool bProcOsc1Phase = (bProcOsc1Sig || subGain > 0.0f);

	bool bProcOsc2Sig = (osc2Gain > 0.0f || ringGain > 0.0f);
	bool bProcOsc2Phase = bProcOsc2Sig;

	// Process phases

#if 1
	// DEBUG: always process
	m_prevPhaseOsc1 = Utils::FreqToPhase(FreqPhaseBuf1, m_prevPhaseOsc1);
	m_prevPhaseOsc2 = Utils::FreqToPhase(FreqPhaseBuf2, m_prevPhaseOsc2);
#else
	// If we need the phase signal, process it. Otherwise, just increment the
	// phase memory by the appropriate amount

	if (bProcOsc1Phase) {
		m_prevPhaseOsc1 = Utils::FreqToPhase(FreqPhaseBuf1, m_prevPhaseOsc1);
	}
	else {
		m_prevPhaseOsc1 = Utils::FreqToPhaseNoProcess(FreqPhaseBuf1, m_prevPhaseOsc1);
	}

	if (bProcOsc2Phase) {
		m_prevPhaseOsc2 = Utils::FreqToPhase(FreqPhaseBuf2, m_prevPhaseOsc2);
	}
	else {
		m_prevPhaseOsc2 = Utils::FreqToPhaseNoProcess(FreqPhaseBuf2, m_prevPhaseOsc2);
	}

	/*
	m_prevPhaseOsc1 = (bProcOsc1Phase ?
		Utils::FreqToPhase(FreqPhaseBuf1, m_prevPhaseOsc1) :
		Utils::FreqToPhaseNoProcess(FreqPhaseBuf1, m_prevPhaseOsc1));

	m_prevPhaseOsc2 = (bProcOsc2Phase ?
		Utils::FreqToPhase(FreqPhaseBuf2, m_prevPhaseOsc2) :
		Utils::FreqToPhaseNoProcess(FreqPhaseBuf2, m_prevPhaseOsc2));
		*/
#endif

	// Process oscs

	if (bProcOsc1Sig) {
		DEBUG_ASSERT(bProcOsc1Phase);

		// TODO: process (FreqPhaseBuf1 -> Osc1Buf)

		// This is just a temporary implementation (this is just an aliasing sawtooth)
		osc1Buf = FreqPhaseBuf1 - 0.5f;

		if (osc1Gain > 0.0f) {
			osc1Buf *= osc1Gain;
			MainBuf += osc1Buf;
		}
	}

	if (bProcOsc2Sig) {
		DEBUG_ASSERT(bProcOsc2Phase);

		// TODO: process (freqPhaseBuf2 -> osc2Buf)

		// This is just a temporary implementation (this is just an aliasing sawtooth)
		osc2Buf = FreqPhaseBuf2 - 0.5f;

		if (osc2Gain > 0.0f) {
			osc2Buf *= osc2Gain;
			MainBuf += osc2Buf;
		}
	}

	// This is the last we need to use osc2Buf, so can use it for ring mod
	if (ringGain > 0.0f) {
		osc2Buf *= osc1Buf;
		osc2Buf *= ringGain;
		MainBuf += osc2Buf;
	}

	// At this point we're done with both osc1Buf and osc2Buf
	// (But we still use freqPhaseBuf1 for sub)
	/*
	if (subGain > 0.0f) {
		// TODO: process (freqPhaseBuf1 -> osc1Buf)
		Osc1Buf *= subGain;
		MainBuf += Osc1Buf;
	}
	*/

	/*
	if (noiseGain > 0.0f) {
		// TODO: process (noise -> osc1Buf)
		Osc1Buf *= noiseGain;
		MainBuf += Osc1Buf;
	}
	*/

	if (!Utils::ApproxEqual(preFiltGain, 1.0f)) {
		MainBuf *= preFiltGain;
	}
}
