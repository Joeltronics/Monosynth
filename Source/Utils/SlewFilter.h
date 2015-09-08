/*
  ==============================================================================

    SlewFilter.h
    Created: 25 Jul 2015 5:13:52pm
    Author:  Joel Geddert

  ==============================================================================
*/

#ifndef SLEWFILTER_H_INCLUDED
#define SLEWFILTER_H_INCLUDED

#include "Utils/Buffer.h"

#include <vector>

namespace Utils
{

class SlewFilter
{
public:
    SlewFilter();
    SlewFilter(float rate);
    
    // Processing functions:
    
    // AudioSampleBuffer - in-place or not
    void Process  (Buffer const& inBuf /*in*/, Buffer& outBuf /*out*/);
    void Process  (Buffer& /*inout*/);
    
    // float* - in-place or not
    void Process  (float const* inBuf /*in*/, float* outBuf /*out*/, uint32_t nSamp /*in*/);
    void Process  (float* buf /*inout*/, uint32_t nSamp /*in*/);
    
    // Single sample
    float Process (float samp /*in*/);
    
    // Other public functions:
    void SetRate(float rate);
    void Clear();
    
    static inline double CalcRate(double rate_per_us, double sampleRate_Hz) {
        double const period_us = 1.0E6 / sampleRate_Hz;
        return rate_per_us * period_us;
    }
    
protected:
    
    float z1;
    float m_rate;
};
    
} //  namespace Engine



#endif  // SLEWFILTER_H_INCLUDED
