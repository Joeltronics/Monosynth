/*
  ==============================================================================

    ApproxEqual.h
    Created: 5 Aug 2015 8:17:26am
    Author:  Joel Geddert

  ==============================================================================
*/

#ifndef APPROXEQUAL_H_INCLUDED
#define APPROXEQUAL_H_INCLUDED

#include "DspUtils.h"

namespace Utils {
    
float const k_defaultApproxEqualThresh = 0.0001f;

template <typename T>
static inline bool ApproxEqual(T a, T b, T thresh) {
    return (std::fabs(a - b) <= thresh);
}

template <typename T>
static inline bool ApproxEqual(T a, T b) {
    return ApproxEqual<T>(a, b, static_cast<T>(k_defaultApproxEqualThresh));
}

static inline bool ApproxEqual(float const* a, float const* b, uint32_t nValues, float thresh) {
#if 1
    float* p = ScopedFloatBuffer(nValues).Get();
    juce::FloatVectorOperations::subtract(p, a, b, nValues);
    juce::FloatVectorOperations::abs(p, p, nValues);
    float max = juce::FloatVectorOperations::findMaximum(p, nValues);
    return (max <= thresh);
#else
    bool bEq = true;
    for (uint32_t n = 0; n < nValues; ++n) {
        bEq = bEq && ApproxEqual<float>(a[n], b[n], thresh);
    }
    return bEq;
#endif
}

static inline bool ApproxEqual(float const* a, float const* b, uint32_t nValues) {
    return ApproxEqual(a, b, nValues, k_defaultApproxEqualThresh);
}

static inline bool ApproxEqual(AudioSampleBuffer const& a, AudioSampleBuffer const& b, float thresh) {
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

static inline bool ApproxEqual(AudioSampleBuffer const& a, AudioSampleBuffer const& b) {
    return ApproxEqual(a, b, k_defaultApproxEqualThresh);
}

} // namespace Utils



#endif  // APPROXEQUAL_H_INCLUDED
