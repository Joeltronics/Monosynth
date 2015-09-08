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

class SynthEngine {
public:
	SynthEngine();
	~SynthEngine();

	void Process(AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
	void PrepareToPlay(double sampleRate, int samplesPerBlock);

private:
	double m_sampleRate;

	Engine::MidiProcessor m_midiProc;
};


#endif  // ENGINE_H_INCLUDED
