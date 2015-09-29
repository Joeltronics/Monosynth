/*
  ==============================================================================

    OnePole.h
    Created: 7 Jul 2015 8:40:41am
    Author:  Joel

  ==============================================================================
*/

#ifndef ONEPOLE_H_INCLUDED
#define ONEPOLE_H_INCLUDED

#include "Utils/Types.h"

#include <vector>

namespace Utils
{

class OnePole
{
    // In all cases here, wc is normalized frequency (fc/fs) - usually between 0 and 0.5
    // Interface is float, but uses doubles internally
    
public:
    OnePole();
    OnePole(double wc);

    // Processing functions:
    
    // Buffer - in-place and not
    void ProcessLowpass  (Buffer const& inBuf /*in*/, Buffer& outBuf /*out*/);
    void ProcessHighpass (Buffer const& inBuf /*in*/, Buffer& outBuf /*out*/);
    void ProcessLowpass  (Buffer& /*inout*/);
    void ProcessHighpass (Buffer& /*inout*/);
    
    // Raw buffer - in-place and not
    void ProcessLowpass  (sample_t const* inBuf /*in*/, sample_t* outBuf /*out*/, size_t nSamp /*in*/);
    void ProcessHighpass (sample_t const* inBuf /*in*/, sample_t* outBuf /*out*/, size_t nSamp /*in*/);
    void ProcessLowpass  (sample_t* buf /*inout*/, uint32_t nSamp /*in*/);
    void ProcessHighpass (sample_t* buf /*inout*/, uint32_t nSamp /*in*/);
    
    // Single sample
    float ProcessLowpass  (sample_t samp /*in*/);
    float ProcessHighpass (sample_t samp /*in*/);
    
    // Other public functions:
    
    void SetFreq(double wc);
    void Clear();
    
protected:
    
    // Vectorized functions
    void  ProcessBufLowpass_ (sample_t const* inBuf, sample_t* outBuf, size_t nSamp);
    void  ProcessBufHighpass_(sample_t const* inBuf, sample_t* outBuf, size_t nSamp);
    void  ProcessBufLowpass_ (Buffer const& inBuf /*in*/, Buffer& outBuf /*out*/);
    void  ProcessBufHighpass_(Buffer const& inBuf /*in*/, Buffer& outBuf /*out*/);
    
    // Coefficient calculation
    void CalcCoeffs_(double wc);

    double z1; // Memory
    double a1; // FB Coeff
    double b0; // FF Coeff
};
   
} // namespace Engine


#endif  // ONEPOLE_H_INCLUDED
