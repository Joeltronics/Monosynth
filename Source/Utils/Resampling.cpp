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

#include "JuceHeader.h"

#define SETUP_RESAMP() \
sample_t const* rp = inBuf.GetConst(); \
sample_t* wp = outBuf.Get()

#define SETUP_UPSAMP(N) \
DEBUG_ASSERT(outBuf.GetLength() == inBuf.GetLength() * (N)); \
size_t const nSamp = inBuf.GetLength(); \
SETUP_RESAMP()

#define SETUP_DOWNSAMP(N) \
DEBUG_ASSERT(inBuf.GetLength() == outBuf.GetLength() * (N)); \
size_t const nSamp = outBuf.GetLength(); \
SETUP_RESAMP()

#define ENABLE_FTZ juce::FloatVectorOperations::enableFlushToZeroMode(true)

namespace  Utils {
    
    // ***** Static functions *****

    void ZeroPadUpsample(Buffer& outBuf, Buffer const& inBuf, uint8_t nUpsamp, bool bScale) {
        SETUP_UPSAMP(nUpsamp);
        
        outBuf.Set(0.f);
        
        for(uint32_t n = 0; n < nSamp; ++n) {
            wp[n*nUpsamp] = rp[n];
        }
        
		if (bScale) {
			outBuf *= sample_t(nUpsamp);
		}
    }
    
    void NearestUpsample(Buffer& outBuf, Buffer const& inBuf, uint8_t nUpsamp) {
        SETUP_UPSAMP(nUpsamp);
        
        for(uint32_t n = 0; n < nSamp; ++n) {
			for (uint8_t m = 0; m < nUpsamp; ++m) {
				wp[n*nUpsamp + m] = rp[n];
			}
        }
    }
    
    void NaiveDownsample(Buffer& outBuf, Buffer const& inBuf, uint8_t nDownsamp, bool bScale) {
        SETUP_DOWNSAMP(nDownsamp);

        for(uint32_t n = 0; n < nSamp; ++n) {
            wp[n] = rp[n*nDownsamp];
        }

		if (bScale) {
			outBuf *= sample_t(nDownsamp);
		}
    }
    
    void AveragingDownsample(Buffer& outBuf, Buffer const& inBuf, uint8_t nDownsamp, bool bScale) {
        SETUP_DOWNSAMP(nDownsamp);
		ENABLE_FTZ;
        
		outBuf.Clear();
            
        for(uint32_t n = 0; n < nSamp; ++n) {
            for(uint8_t m = 0; m < nDownsamp; ++m)
                wp[n] += rp[n*nDownsamp + m];
        }
        
		if (!bScale) {
			outBuf /= sample_t(nDownsamp);
		}
    }
    
    // ***** LinearInterpUpsampler *****
    
    LinearInterpUpsampler::LinearInterpUpsampler(uint8_t nUpsamp, uint8_t nChan, bool bMinGroupDelay) :
        m_nUpsamp(nUpsamp),
        m_nChan(nChan),
        m_bMinDelay(bMinGroupDelay)
    {
        Reset_();
    }
    
    void LinearInterpUpsampler::Process(Buffer& outBuf, Buffer const& inBuf) {
        SETUP_UPSAMP(m_nUpsamp);
		ENABLE_FTZ;
		
        float const interpMult = 1.0f/float(m_nUpsamp);
        
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
                wp[nOut++] = m_lastSamp;
                
            // Interpolate
            for (uint8_t m = 1; m < m_nUpsamp; ++m)
                wp[nOut++] = m_lastSamp + ((rp[nIn] - m_lastSamp) * m*interpMult);
                
            if (m_bMinDelay)
                wp[nOut++] = rp[nIn];
                
			m_lastSamp = rp[nIn++];
        }
    }
    
    void LinearInterpUpsampler::Reset_() {
		m_lastSamp = 0.f;
    }
} // namespace Utils



