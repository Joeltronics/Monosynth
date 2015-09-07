/*
  ==============================================================================

    Engine.cpp
    Created: 7 Sep 2015 12:30:58pm
    Author:  Joel

  ==============================================================================
*/

#include "Engine.h"



SynthEngine::SynthEngine() {}
SynthEngine::~SynthEngine() {}

void SynthEngine::Process(AudioSampleBuffer& buffer, MidiBuffer& midiMessages) {

}

void SynthEngine::PrepareToPlay(double sampleRate, int samplesPerBlock) {
	m_sampleRate = sampleRate;
}

