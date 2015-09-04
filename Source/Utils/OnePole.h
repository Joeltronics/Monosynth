/*
  ==============================================================================

    OnePole.h
    Created: 7 Jul 2015 8:40:41am
    Author:  Joel

  ==============================================================================
*/

#ifndef ONEPOLE_H_INCLUDED
#define ONEPOLE_H_INCLUDED

#include "JuceHeader.h"

#include <vector>

namespace Utils
{

class OnePole
{
    // In all cases here, wc is normalized frequency (fc/fs) - usually between 0 and 0.5
    // Interface is float, but uses doubles internally
    
public:
    OnePole(uint8_t nChannels);
    OnePole(uint8_t nChannels, float wc);

    // Processing functions:
    
    // AudioSampleBuffer - in-place and not
    void ProcessLowpass  (AudioSampleBuffer const& inBuf /*in*/, AudioSampleBuffer& outBuf /*out*/);
    void ProcessHighpass (AudioSampleBuffer const& inBuf /*in*/, AudioSampleBuffer& outBuf /*out*/);
    void ProcessLowpass  (AudioSampleBuffer& /*inout*/);
    void ProcessHighpass (AudioSampleBuffer& /*inout*/);
    
    // Raw buffer - in-place and not
    void ProcessLowpass  (float const* inBuf /*in*/, float* outBuf /*out*/, uint32_t nSamp /*in*/, uint8_t channel /*in*/);
    void ProcessHighpass (float const* inBuf /*in*/, float* outBuf /*out*/, uint32_t nSamp /*in*/, uint8_t channel /*in*/);
    void ProcessLowpass  (float* buf /*inout*/, uint32_t nSamp /*in*/, uint8_t channel /*in*/);
    void ProcessHighpass (float* buf /*inout*/, uint32_t nSamp /*in*/, uint8_t channel /*in*/);
    
    // Single sample
    float ProcessLowpass  (float samp /*in*/, uint8_t channel /*in*/);
    float ProcessHighpass (float samp /*in*/, uint8_t channel /*in*/);
    
    // Other public functions:
    
    void SetFreq(float wc);
    void SetNumChannels(uint8_t nChan); // will call Clear() if changed
    void Clear();
    
protected:
    
    // Vectorized functions
    void  ProcessBufLowpass_(float const* inBuf, float* outBuf, uint32_t nSamp, uint8_t chan);
    void  ProcessBufHighpass_(float const* inBuf, float* outBuf, uint32_t nSamp, uint8_t chan);
    void  ProcessBufLowpass_(AudioSampleBuffer const& inBuf /*in*/, AudioSampleBuffer& outBuf /*out*/);
    void  ProcessBufHighpass_(AudioSampleBuffer const& inBuf /*in*/, AudioSampleBuffer& outBuf /*out*/);
    
    // Coefficient calculation
    void CalcCoeffs_(float wc);

    uint8_t m_nChannels;
    
    std::vector<double> z1; // Memory (one per channel)
    double a1; // FB Coeff
    double b0; // FF Coeff
};
   
} // namespace Engine


#endif  // ONEPOLE_H_INCLUDED
