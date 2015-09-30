/*
  ==============================================================================

    PitchProcessor.h
    Created: 15 Sep 2015 8:13:01am
    Author:  Joel

  ==============================================================================
*/

#ifndef PITCHPROCESSOR_H_INCLUDED
#define PITCHPROCESSOR_H_INCLUDED

#include "Types.h"

#include <cmath>

#include "Utils/DspUtils.h"

namespace Engine {

class PitchProcessor {
public:

	PitchProcessor() : m_sampleRate(0.0) {}
	~PitchProcessor() {}

	void PrepareToPlay(double sampleRate, int /*samplesPerBlock*/) { m_sampleRate = sampleRate; }

	inline float PitchToNormFreq(float pitch) {
		return float(Utils::PitchToFreqHz<double>(pitch) / m_sampleRate);
	}
	
	void PitchToFreq(Buffer& buf);
	void PitchToFreq(Buffer const& inBuf, Buffer& outBuf);

private:

	double m_sampleRate;
};

}



#endif  // PITCHPROCESSOR_H_INCLUDED
