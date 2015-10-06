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
#include "Utils/Debug.h"
#include "Utils/OnePole.h"

namespace Engine {

class PitchProcessor {
public:

	PitchProcessor();
	~PitchProcessor();

	void PrepareToPlay(double sampleRate, int samplesPerBlock);

	inline float PitchToNormFreq(float pitch) {
		DEBUG_ASSERT(m_sampleRate > 0.0);
		return float(Utils::PitchToFreqHz<double>(pitch) / m_sampleRate);
	}
	
	void PitchToFreq(Buffer& buf);
	void PitchToFreq(Buffer const& inBuf, Buffer& outBuf);

	void ProcessPitchBend(Buffer& pitchBuf /*inout*/, eventBuf_t<uint16_t> const& pitchBendEvents, uint32_t pitchBendAmt);

private:

	double m_sampleRate;
	uint16_t m_lastPitchBend;
	Utils::OnePole m_pitchBendFilt;
};

}



#endif  // PITCHPROCESSOR_H_INCLUDED
