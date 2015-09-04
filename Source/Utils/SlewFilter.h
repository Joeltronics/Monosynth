/*
  ==============================================================================

    SlewFilter.h
    Created: 25 Jul 2015 5:13:52pm
    Author:  Joel Geddert

  ==============================================================================
*/

#ifndef SLEWFILTER_H_INCLUDED
#define SLEWFILTER_H_INCLUDED

#include "JuceHeader.h"

#include <vector>

namespace Utils
{

class SlewFilter
{
public:
    SlewFilter(uint8_t nChannels);
    SlewFilter(uint8_t nChannels, float rate);
    
    // Processing functions:
    
    // AudioSampleBuffer - in-place or not
    void Process  (AudioSampleBuffer const& inBuf /*in*/, AudioSampleBuffer& outBuf /*out*/);
    void Process  (AudioSampleBuffer& /*inout*/);
    
    // float* - in-place or not
    void Process  (float const* inBuf /*in*/, float* outBuf /*out*/, uint32_t nSamp /*in*/, uint8_t channel /*in*/);
    void Process  (float* buf /*inout*/, uint32_t nSamp /*in*/, uint8_t channel /*in*/);
    
    // Single sample
    float Process (float samp /*in*/, uint8_t channel /*in*/);
    
    // Other public functions:
    void SetRate(float rate);
    void SetNumChannels(uint8_t nChan);
    void Clear();
    
    static inline float CalcRate(float rate_per_us, float sampleRate_Hz) {
        float const period_us = 1.0E6 / sampleRate_Hz;
        return rate_per_us * period_us;
    }
    
protected:
    
    uint8_t m_nChannels;
    std::vector<float> z1;
    float m_rate;
};
    
} //  namespace Engine



#endif  // SLEWFILTER_H_INCLUDED
