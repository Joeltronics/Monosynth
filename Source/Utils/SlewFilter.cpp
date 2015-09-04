/*
  ==============================================================================

    SlewFilter.cpp
    Created: 25 Jul 2015 5:13:52pm
    Author:  Joel Geddert

  ==============================================================================
*/

#include "SlewFilter.h"

#include "Debug.h"
#include "DspUtils.h"

namespace Utils
{

namespace Detail
{
    static inline float Process(float samp, float prevSamp, float rate)
    {
        float delta = samp - prevSamp;
        delta = Utils::Clip(delta, rate);
        return prevSamp + delta;
    }
}
 
// ***** Constructors *****
    
SlewFilter::SlewFilter(uint8_t nChannels) :
    m_nChannels(nChannels),
    m_rate(1.0f)
{
    Clear();
}
    
SlewFilter::SlewFilter(uint8_t nChannels, float rate) :
    m_nChannels(nChannels),
    m_rate(rate)
{
    Clear();
}

// ***** Process *****

// Buffer
void SlewFilter::Process(AudioSampleBuffer const& inBuf /*in*/, AudioSampleBuffer& outBuf /*out*/)
{
    DEBUG_ASSERT(inBuf.getNumChannels() == outBuf.getNumChannels());
    DEBUG_ASSERT(inBuf.getNumChannels() == m_nChannels);
    DEBUG_ASSERT(inBuf.getNumSamples() == outBuf.getNumSamples());
    
    // TODO: invert loop order so iterating channels is on the inside
    uint32_t const nSamp = inBuf.getNumSamples();
    for(uint8_t chan = 0; chan < m_nChannels; ++chan) {
        float* wp = outBuf.getWritePointer(chan);
        float const* rp = inBuf.getReadPointer(chan);
        Process(rp, wp, nSamp, chan);
    }
}

// Buffer - in-place
void SlewFilter::Process(AudioSampleBuffer& buf /*inout*/)
{
    DEBUG_ASSERT(buf.getNumChannels() == m_nChannels);
    
    // TODO: invert loop order so iterating channels is on the inside
    uint32_t const nSamp = buf.getNumSamples();
    for(uint8_t chan = 0; chan < m_nChannels; ++chan) {
        float* wp = buf.getWritePointer(chan);
        Process(wp, nSamp, chan);
    }
}

// Raw buffer
void SlewFilter::Process(float const* inBuf /*in*/, float* outBuf /*out*/, uint32_t nSamp /*in*/, uint8_t chan /*in*/)
{
    float z = z1[chan];
    for (uint32_t n=0; n < nSamp; n++) {
        z = Detail::Process(inBuf[n], z, m_rate);
        outBuf[n] = z;
    }
    z1[chan] = z;
}

// Raw buffer - in-place
void SlewFilter::Process(float* buf /*inout*/, uint32_t nSamp /*in*/, uint8_t chan /*in*/)
{
    Process(buf, buf, nSamp, chan);
}

// Single sample
float SlewFilter::Process(float samp /*in*/, uint8_t chan /*in*/) {
    float const out = Detail::Process(samp, z1[chan], m_rate);
    z1[chan] = out;
    return out;
}

// ***** Other public functions *****

void SlewFilter::SetRate(float rate)
{
    m_rate = rate;
}
    
void SlewFilter::SetNumChannels(uint8_t nChan) {
    if (nChan != m_nChannels) {
        m_nChannels = nChan;
        Clear();
    }
}

void SlewFilter::Clear() {
    z1.assign(m_nChannels, 0.0f);
}
    
} // namespace Engine