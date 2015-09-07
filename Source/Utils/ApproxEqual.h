/*
  ==============================================================================

    ApproxEqual.h
    Created: 5 Aug 2015 8:17:26am
    Author:  Joel Geddert

  ==============================================================================
*/

#ifndef APPROXEQUAL_H_INCLUDED
#define APPROXEQUAL_H_INCLUDED

#include "Types.h"
#include "JuceHeader.h"

namespace Utils {

static inline bool ApproxEqual(float a, float b, float thresh = k_defaultApproxEqualThresh) {
    return (std::fabs(a - b) <= thresh);
}

static inline bool ApproxEqual(double a, double b, double thresh = k_defaultApproxEqualThresh) {
	return (std::fabs(a - b) <= thresh);
}

static inline bool ApproxEqual(sample_t const* a, sample_t const* b, uint32_t nValues, sample_t thresh = k_defaultApproxEqualThresh) {
	// TODO: test and see which is faster
#if 1
    sample_t* p = Buffer(nValues).Get();
    juce::FloatVectorOperations::subtract(p, a, b, nValues);
    juce::FloatVectorOperations::abs(p, p, nValues);
    float max = juce::FloatVectorOperations::findMaximum(p, nValues);
    return (max <= thresh);
#else
    bool bEq = true;
    for (uint32_t n = 0; n < nValues; ++n) {
        bEq = bEq && ApproxEqual(a[n], b[n], thresh);
    }
    return bEq;
#endif
}

static inline bool ApproxEqual(Buffer const& a, Buffer const& b, float thresh = k_defaultApproxEqualThresh) {
	if (a.GetLength() != b.GetLength()) return false;
	return ApproxEqual(a.GetConst(), b.GetConst(), a.GetLength(), thresh);
}

static inline bool ApproxEqual(juce::AudioSampleBuffer const& a, juce::AudioSampleBuffer const& b, float thresh = k_defaultApproxEqualThresh) {
    if (a.getNumChannels() != b.getNumChannels() || a.getNumSamples() != b.getNumSamples())
        return false;
    uint8_t const nChan = a.getNumChannels();
    uint32_t const nSamp = a.getNumSamples();
    bool bEq = true;
    for (uint8_t chan = 0; chan < nChan; ++chan) {
        bEq = bEq && ApproxEqual(a.getReadPointer(chan), b.getReadPointer(chan), nSamp, thresh);
    }
    return bEq;
}

} // namespace Utils



#endif  // APPROXEQUAL_H_INCLUDED
