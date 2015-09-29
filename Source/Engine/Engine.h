/*
  ==============================================================================

    Engine.h
    Created: 7 Sep 2015 12:30:58pm
    Author:  Joel

  ==============================================================================
*/

#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "JuceHeader.h"

#include "Types.h"
#include "MidiProcessor.h"
#include "PitchProcessor.h"
#include "Envelope.h"

class SynthEngine {
public:
	SynthEngine();
	~SynthEngine();

	void PrepareToPlay(double sampleRate, int samplesPerBlock);

	void Process(juce::AudioSampleBuffer& buffer, juce::MidiBuffer& midiMessages);
	
private:
	void ProcessOscsAndMixer_(Buffer& MainBuf, Buffer& FreqPhaseBuf1, Buffer& FreqPhaseBuf2);

	double m_sampleRate;
    
   	uint8_t m_lastNote;
    
	float m_prevPhaseOsc1;
	float m_prevPhaseOsc2;

	Engine::MidiProcessor m_midiProc;
	Engine::PitchProcessor m_pitchProc;

	Engine::GateEnvelope m_ampEnv;
	Engine::AdsrEnvelope m_filtEnv;
};


#endif  // ENGINE_H_INCLUDED
