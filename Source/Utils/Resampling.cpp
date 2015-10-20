/*
  ==============================================================================

    Resampling.cpp
    Created: 4 Aug 2015 8:15:40am
    Author:  Joel Geddert

  ==============================================================================
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Resampling.h"

#include "Debug.h"

using namespace juce;

// nChan std::min is fallback behavior if assert fails
// (for release builds where assert may be defined as nothing)
#define SETUP_UPSAMP(N) \
DEBUG_ASSERT(inBuf.getNumChannels() == outBuf.getNumChannels()); \
DEBUG_ASSERT(outBuf.getNumSamples() == inBuf.getNumSamples() * (N)); \
size_t const nChan = std::min(inBuf.getNumChannels(),outBuf.getNumChannels()); \
size_t const nSamp = inBuf.getNumSamples()

#define SETUP_DOWNSAMP(N) \
DEBUG_ASSERT(inBuf.getNumChannels() == outBuf.getNumChannels()); \
DEBUG_ASSERT(inBuf.getNumSamples() == outBuf.getNumSamples() * (N)); \
size_t const nChan = std::min(inBuf.getNumChannels(),outBuf.getNumChannels()); \
size_t const nSamp = outBuf.getNumSamples()

namespace  Utils {
    
    // ***** Static functions *****

    void ZeroPadUpsample(AudioSampleBuffer& outBuf, AudioSampleBuffer const& inBuf, uint8_t nUpsamp, bool bScale) {
        SETUP_UPSAMP(nUpsamp);
        
        outBuf.clear();
        
        for(uint8_t chan = 0; chan < nChan; ++chan) {
            float const* rp = inBuf.getReadPointer(chan);
            float* wp = outBuf.getWritePointer(chan);
            
            for(uint32_t n = 0; n < nSamp; ++n) {
                wp[n*nUpsamp] = rp[n];
            }
        }
        
        if (bScale)
            outBuf.applyGain(float(nUpsamp));
    }
    
    void NearestUpsample(AudioSampleBuffer& outBuf, AudioSampleBuffer const& inBuf, uint8_t nUpsamp) {
        SETUP_UPSAMP(nUpsamp);
        
        for(uint8_t chan = 0; chan < nChan; ++chan) {
            float const* rp = inBuf.getReadPointer(chan);
            float* wp = outBuf.getWritePointer(chan);
            
            for(uint32_t n = 0; n < nSamp; ++n) {
                for(uint8_t m = 0; m < nUpsamp; ++m)
                    wp[n*nUpsamp + m] = rp[n];
            }
        }
    }
    
    void NaiveDownsample(AudioSampleBuffer& outBuf, AudioSampleBuffer const& inBuf, uint8_t nDownsamp, bool bScale) {
        SETUP_DOWNSAMP(nDownsamp);
        
        for(uint8_t chan = 0; chan < nChan; ++chan) {
            float const* rp = inBuf.getReadPointer(chan);
            float* wp = outBuf.getWritePointer(chan);
            
            for(uint32_t n = 0; n < nSamp; ++n) {
                wp[n] = rp[n*nDownsamp];
            }
            
        }
        
        if (bScale)
            outBuf.applyGain(float(nDownsamp));
    }
    
    void AveragingDownsample(AudioSampleBuffer& outBuf, AudioSampleBuffer const& inBuf, uint8_t nDownsamp, bool bScale) {
        SETUP_DOWNSAMP(nDownsamp);
        
        for(uint8_t chan = 0; chan < nChan; ++chan) {
            float const* rp = inBuf.getReadPointer(chan);
            float* wp = outBuf.getWritePointer(chan);
            
            juce::FloatVectorOperations::clear(wp, nSamp);
            
            for(uint32_t n = 0; n < nSamp; ++n) {
                for(uint8_t m = 0; m < nDownsamp; ++m)
                    wp[n] += rp[n*nDownsamp + m];
            }
        }
        
        if (!bScale)
            outBuf.applyGain(1.0f/float(nDownsamp));
    }
    
    // ***** LinearInterpUpsampler *****
    
        LinearInterpUpsampler::LinearInterpUpsampler(uint8_t nUpsamp, uint8_t nChan, bool bMinGroupDelay) :
        m_nUpsamp(nUpsamp),
        m_nChan(nChan),
        m_bMinDelay(bMinGroupDelay)
    {
        Reset_();
    }
    
    LinearInterpUpsampler::LinearInterpUpsampler(uint8_t nUpsamp, uint8_t nChan) :
        m_nUpsamp(nUpsamp),
        m_nChan(nChan),
        m_bMinDelay(false)
    {
        Reset_();
    }
    
    void LinearInterpUpsampler::Process(AudioSampleBuffer const& inBuf, AudioSampleBuffer& outBuf) {
        SETUP_UPSAMP(m_nUpsamp);
        
        float const interpMult = 1.0f/float(m_nUpsamp);
        
        for (uint8_t chan = 0; chan < nChan; ++chan) {
            float const* rp = inBuf.getReadPointer(chan);
            float* wp = outBuf.getWritePointer(chan);
            
            float& last = m_lastSamp[chan];
            
            /*
            Example, while upsampling by 4:
            
                    If integer delay        If min delay
            
            wp[0] = rp[-1]             f(rp[-1], rp[0])
            wp[1] = f(rp[-1], rp[0])   f(rp[-1], rp[0])
            wp[2] = f(rp[-1], rp[0])   f(rp[-1], rp[0])
            wp[3] = f(rp[-1], rp[0])   rp[0]
            wp[4] = rp[0]              f(rp[0], rp[1])
            wp[5] = f(rp[0], rp[1])    f(rp[0], rp[1])
            wp[6] = f(rp[0], rp[1])    f(rp[0], rp[1])
            wp[7] = f(rp[0], rp[1])    rp[1]
            */
            
            uint32_t nOut = 0;
            uint32_t nIn = 0;
            while (nOut < (nSamp*m_nUpsamp)) {
                
                if (!m_bMinDelay)
                    wp[nOut++] = last;
                
                // Interpolate
                for (uint8_t m = 1; m < m_nUpsamp; ++m)
                    wp[nOut++] = last + ((rp[nIn] - last) * m*interpMult);
                
                if (m_bMinDelay)
                    wp[nOut++] = rp[nIn];
                
                last = rp[nIn++];
            }
        }
    }
    
    void LinearInterpUpsampler::Reset_() {
        m_lastSamp.assign(m_nChan, 0.0);
    }

    // ***** FirUpsampler *****
    // TODO
    
    // ***** FirDownsampler *****
    // TODO
    
}



