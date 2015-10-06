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
#include "Oscillator.h"
#include "Vca.h"

class SynthEngine {
public:
	SynthEngine();
	~SynthEngine();

	void PrepareToPlay(double sampleRate, int samplesPerBlock);

	void Process(juce::AudioSampleBuffer& buffer, juce::MidiBuffer& midiMessages);
	
private:
	void ProcessOscsAndMixer_(Buffer& mainBuf /*out*/, Buffer& osc1freq /*inout*/, Buffer& osc2freq /*inout*/);

	double m_sampleRate;
    
   	uint8_t m_lastNote;
    
	float m_prevPhaseOsc1;
	float m_prevPhaseOsc2;

	Engine::MidiProcessor m_midiProc;
	Engine::PitchProcessor m_pitchProc;

	Engine::AdsrEnvelope m_filtEnv;

	Engine::Oscillator m_osc1;
	Engine::Oscillator m_osc2;
	Engine::Oscillator m_subOsc;

	Engine::Vca m_vca;
};


#endif  // ENGINE_H_INCLUDED
