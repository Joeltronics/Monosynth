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


SynthEngine::SynthEngine() {}
SynthEngine::~SynthEngine() {}

void SynthEngine::Process(juce::AudioSampleBuffer& juceBuf, juce::MidiBuffer& midiMessages) {
	
	size_t nSamp = juceBuf.getNumSamples();
	size_t nChan = juceBuf.getNumChannels();

	Buffer buf(juceBuf.getWritePointer(0), nSamp);

	// Process:
	// 1. MIDI
	// 2. Mod sources (Env/LFO)
	// 3. Pitch
	// 4. Oscillators
	// 5. Mixer
	// 6. Filter
	// 7. Distortion
	// 8. VCA
	// 9. Effects

	eventBuf_t<gateEvent_t> gateEvents;
	eventBuf_t<uint8_t> noteEvents;
	eventBuf_t<uint8_t> velEvents;
	eventBuf_t<int> pitchBendEvents;

	// 1. MIDI
	m_midiProc.Process( nSamp, midiMessages, gateEvents, noteEvents, velEvents, pitchBendEvents);

	// If not mono, copy channel 0 to all others
	for (size_t chan = 1; chan < nChan; ++chan)
		juce::FloatVectorOperations::copy(juceBuf.getWritePointer(0), juceBuf.getReadPointer(chan), nSamp);
}

void SynthEngine::PrepareToPlay(double sampleRate, int /*samplesPerBlock*/) {
	m_sampleRate = sampleRate;
}

