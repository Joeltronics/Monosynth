/*
  ==============================================================================

    Oscillator.h
    Created: 5 Oct 2015 9:14:41pm
    Author:  Joel

  ==============================================================================
*/

#ifndef OSCILLATOR_H_INCLUDED
#define OSCILLATOR_H_INCLUDED

#include "JuceHeader.h"
#include "Types.h"

namespace Engine {

class Oscillator {
public:
	Oscillator() : m_sampleRate(0.0), m_phase(0.0f) {}
	~Oscillator() {}

	// TODO: randomize phase
	void PrepareToPlay(double sampleRate, int /*samplesPerBlock*/) { m_sampleRate = sampleRate; }

	void ProcessFromFreq(Buffer& audioBuf /*out*/, Buffer& freqPhaseBuf /*inout*/);
	
	void ProcessSynced(Buffer& audioBuf /*out*/, Buffer& freqBuf /*inout*/, Buffer const& syncPhaseBuf /*in*/);
	
	void ProcessSub(Buffer& audioBuf /*out*/, Buffer const& phaseBuf /*in*/);

private:
	float m_phase;
	double m_sampleRate;
};

}

#endif  // OSCILLATOR_H_INCLUDED
