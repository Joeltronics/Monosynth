/*
  ==============================================================================

    OnePole.cpp
    Created: 7 Jul 2015 8:40:41am
    Author:  Joel

  ==============================================================================
*/

#include "OnePole.h"

#include "Debug.h"
#include "DspUtils.h"

#define _USE_MATH_DEFINES
#include <cmath>
//#include <math.h>

namespace Utils
{

// ***** Constructors *****

OnePole::OnePole(uint8_t nChannels) :
    m_nChannels(nChannels),
    a1(0.0),
    b0(1.0)
{
    Clear();
}
    
OnePole::OnePole(uint8_t nChannels, float wc) :
    m_nChannels(nChannels)
{
    Clear();
    CalcCoeffs_(wc);
}

// ***** Process *****
    
void OnePole::ProcessLowpass(AudioSampleBuffer& buf /*inout*/) {
    DEBUG_ASSERT(buf.getNumChannels() == m_nChannels);
    ProcessBufLowpass_(buf, buf);
}
    
void OnePole::ProcessHighpass(AudioSampleBuffer& buf /*inout*/) {
    DEBUG_ASSERT(buf.getNumChannels() == m_nChannels);
    ProcessBufHighpass_(buf, buf);
}
    
void OnePole::ProcessLowpass(AudioSampleBuffer const& inBuf, AudioSampleBuffer& outBuf) {
    DEBUG_ASSERT(inBuf.getNumChannels() == outBuf.getNumChannels());
    DEBUG_ASSERT(inBuf.getNumChannels() == m_nChannels);
    DEBUG_ASSERT(inBuf.getNumSamples() == outBuf.getNumSamples());
    ProcessBufLowpass_(inBuf, outBuf);
}

void OnePole::ProcessHighpass(AudioSampleBuffer const& inBuf, AudioSampleBuffer& outBuf) {
    DEBUG_ASSERT(inBuf.getNumChannels() == outBuf.getNumChannels());
    DEBUG_ASSERT(inBuf.getNumChannels() == m_nChannels);
    DEBUG_ASSERT(inBuf.getNumSamples() == outBuf.getNumSamples());
    ProcessBufHighpass_(inBuf, outBuf);
}

void OnePole::ProcessLowpass(float* buf /*inout*/, uint32_t nSamp, uint8_t chan) {
    ProcessBufLowpass_(buf, buf, nSamp, chan);
}
    
void OnePole::ProcessHighpass(float* buf /*inout*/, uint32_t nSamp, uint8_t chan) {
    ProcessBufHighpass_(buf, buf, nSamp, chan);
}

void OnePole::ProcessLowpass(float const* inBuf, float* outBuf /*out*/, uint32_t nSamp, uint8_t chan) {
    ProcessBufLowpass_(inBuf, outBuf, nSamp, chan);
}

void OnePole::ProcessHighpass(float const* inBuf, float* outBuf /*out*/, uint32_t nSamp, uint8_t chan) {
    ProcessBufHighpass_(inBuf, outBuf, nSamp, chan);
}
    
float OnePole::ProcessLowpass(float samp, uint8_t chan) {
    z1[chan] = b0*double(samp) + a1*z1[chan];
    return z1[chan];
}

float OnePole::ProcessHighpass(float samp, uint8_t chan) {
    z1[chan] = b0*double(samp) + a1*z1[chan];
    return samp - float(z1[chan]);
}
    
// ***** Private processing functions *****
    
// TODO: vectorize these!
/*
Could easily vectorize b0*samp calc - but because we're multiplying a float by
a double, can't easily do this vectorized
 
There are also more complicated ways to fully fectorize IIR filters:
http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.217.5808&rep=rep1&type=pdf
http://reanimator-web.appspot.com/articles/simdiir
http://dsp.stackexchange.com/questions/1075/how-can-i-vectorize-the-computations-for-a-first-order-recursive-filter
*/

void OnePole::ProcessBufLowpass_(float const* inBuf, float* outBuf, uint32_t nSamp, uint8_t chan)
{
    double z = z1[chan];
    for (uint32_t n=0; n < nSamp; n++) {
        z = b0*double(inBuf[n]) + a1*z;
        outBuf[n] = z;
    }
    z1[chan] = z;
}

void OnePole::ProcessBufHighpass_(float const* inBuf, float* outBuf, uint32_t nSamp, uint8_t chan)
{
    // Process as lowpass, but into temporary buffer
    // No need to copy; just allocate
    AudioSampleBuffer lowpassBuf(1, nSamp);
    float* pLowpassBuf = lowpassBuf.getWritePointer(0);
    
    ProcessBufLowpass_(inBuf, pLowpassBuf, nSamp, chan);
    
    // Then subtract to make it highpass
    juce::FloatVectorOperations::subtract(outBuf, inBuf, pLowpassBuf, nSamp);
}

// Like the float* version, but we unroll channels inside of sample numbers
// because an IIR filter causes pipeline stall since we need to wait for the result
// before processing the next sample. Might as well use that stalled time to process
// the other channel!
void OnePole::ProcessBufLowpass_(AudioSampleBuffer const& inBuf, AudioSampleBuffer& outBuf)
{
    uint32_t const nSamp = inBuf.getNumSamples();
    
    if (m_nChannels == 1) {
        ProcessBufLowpass_(inBuf.getReadPointer(0), outBuf.getWritePointer(0), nSamp, 0);
    }
    else if (m_nChannels == 2) {
        // I don't know if compiler is smart enough to unroll this
        // Stereo will be most common use case though, so we'll be explicit to ensure max performance
        float* outBufL = outBuf.getWritePointer(0);
        float* outBufR = outBuf.getWritePointer(1);
        float const* inBufL = inBuf.getReadPointer(0);
        float const* inBufR = inBuf.getReadPointer(1);
        double zL = z1[0];
        double zR = z1[1];
        for (uint32_t n=0; n < nSamp; n++) {
            // inBuf values will be promoted to double here
            zL = b0*inBufL[n] + a1*zL;
            zR = b0*inBufR[n] + a1*zR;
            outBufL[n] = zL;
            outBufR[n] = zR;
        }
        z1[0] = zL;
        z1[1] = zR;
    }
    else {
        std::vector<float const*> inBufs(m_nChannels);
        std::vector<float*> outBufs(m_nChannels);
        
        for(uint8_t chan = 0; chan < m_nChannels; ++chan) {
            inBufs[chan] = inBuf.getReadPointer(chan);
            outBufs[chan] = outBuf.getWritePointer(chan);
        }
        
        for(uint32_t n = 0; n < nSamp; n++) {
            for(uint8_t chan = 0; chan < m_nChannels; ++chan) {
                double const x = inBufs[chan][n];
                z1[chan] = b0*x + a1*z1[chan];
                outBufs[chan][n] = z1[chan];
            }
        }
    }
}

void OnePole::ProcessBufHighpass_(AudioSampleBuffer const& inBuf /*in*/, AudioSampleBuffer& outBuf /*out*/)
{
    uint32_t const nSamp = inBuf.getNumSamples();
    
    // Process as lowpass, but into temporary buffer
    // No need to copy; just allocate
    AudioSampleBuffer lowpassBuf(m_nChannels, nSamp);
    ProcessBufLowpass_(inBuf, lowpassBuf);
    
    // Then subtract to make it highpass
    for(uint8_t chan = 0; chan < m_nChannels; ++chan) {
        float const* pInBuf = inBuf.getReadPointer(chan);
        float const* pLowpassBuf = lowpassBuf.getReadPointer(chan);
        float* pOutBuf = outBuf.getWritePointer(chan);
        juce::FloatVectorOperations::subtract(pOutBuf, pInBuf, pLowpassBuf, nSamp);
    }
}
    
// ***** Other public functions *****
    
void OnePole::SetFreq(float wc) {
    CalcCoeffs_(wc);
}

void OnePole::SetNumChannels(uint8_t nChan) {
    if (nChan != m_nChannels) {
        m_nChannels = nChan;
        Clear();
    }
}
    
void OnePole::Clear() {
    z1.assign(m_nChannels, 0.0);
}
    
// ***** Other Private functions *****

void OnePole::CalcCoeffs_(float wc) {
    a1 = exp(-2.0f*M_PI * double(wc));
    b0 = 1.0 - a1;
}

   
} // namespace Engine