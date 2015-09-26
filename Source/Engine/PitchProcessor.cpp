/*
  ==============================================================================

    PitchProcessor.cpp
    Created: 15 Sep 2015 8:13:01am
    Author:  Joel

  ==============================================================================
*/

#include "PitchProcessor.h"

#include "Types.h"

#include <cmath>

namespace Engine {

void PitchProcessor::PitchToFreq(Buffer& buf) {
	float* p = buf.Get();
	for (size_t n = 0; n < buf.GetLength(); ++n) {
		p[n] = PitchToNormFreq(p[n]);
	}
}
void PitchProcessor::PitchToFreq(Buffer const& inBuf, Buffer& outBuf) {
	DEBUG_ASSERT(inBuf.GetLength() == outBuf.GetLength());

	float const* pIn = inBuf.GetConst();
	float* pOut = outBuf.Get();

	for (size_t n = 0; n < inBuf.GetLength(); ++n) {
		pOut[n] = PitchToNormFreq(pIn[n]);
	}
}

}