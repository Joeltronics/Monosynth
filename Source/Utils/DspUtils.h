/*
  ==============================================================================

    dsputils.h
    Created: 16 Jul 2015 7:57:05pm
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

#ifndef DSPUTILS_H_INCLUDED
#define DSPUTILS_H_INCLUDED

// Requires C++11 or higher

// Disable "unreferenced local function has been removed"
#pragma warning (disable: 4505)

#include "JuceHeader.h"

#include "Debug.h"
#include "Utils/Types.h"

#include <cmath>

#include <algorithm>

namespace Utils
{
	template <typename I>
	static inline int RoundTo(float f) { return static_cast<I>(std::round(f)); }
	template <typename I>
	static inline int RoundTo(double d) { return static_cast<I>(std::round(d)); }

    static inline float  AmpTodB(float  amp) {return 20.0f * log10f(amp);}
	static inline double AmpTodB(double amp) {return 20.0  * log10 (amp);}
	static inline float  PowTodB(float  pow) {return 10.0f * log10f(pow);}
	static inline double PowTodB(double pow) {return 10.0  * log10 (pow);}
	static inline float  dBtoAmp(float  dB)  {return powf(10.0f, dB/20.0f);}
	static inline double dBtoAmp(double dB)  {return pow (10.0 , dB/20.0 );}
	static inline float  dBtoPow(float  dB)  {return powf(10.0f, dB/10.0f);}
	static inline double dBtoPow(double dB)  {return pow (10.0 , dB/10.0 );}

	template <typename T>
	static inline T PitchToFreqHz(T pitch) {
		return T(440.0 * pow(2.0, (double(pitch) - 69.0) / 12.0));
	}

    static inline void CopyAudioSampleBuffer(juce::AudioSampleBuffer const& inBuf, juce::AudioSampleBuffer& outBuf) {
        size_t const nChan = inBuf.getNumChannels();
        size_t const nSamp = inBuf.getNumSamples();
        
        DEBUG_ASSERT(size_t(outBuf.getNumChannels()) == nChan);
        DEBUG_ASSERT(size_t(outBuf.getNumSamples()) == nSamp);
        
        for (uint8_t chan = 0; chan < nChan; ++chan) {
            float* wp = outBuf.getWritePointer(chan);
            float const* rp = inBuf.getReadPointer(chan);

            juce::FloatVectorOperations::copy(wp, rp, nSamp);
        }
    }
    
    static inline juce::AudioSampleBuffer CreateAudioSampleBufferDeepCopy(juce::AudioSampleBuffer const& otherBuf) {
        size_t const nChan = otherBuf.getNumChannels();
        size_t const nSamp = otherBuf.getNumSamples();
        juce::AudioSampleBuffer newBuf(nChan, nSamp);
        
        CopyAudioSampleBuffer(otherBuf, newBuf);
        
        return newBuf;
    }
    
    /**
     * Simulates typical logarithmic pot (which actually uses piecewise approximation)
     * Piecewise linear function:
     * (0,0) (0.5,0.2) (1,1)
     * Pos = position, 0-1
     */
    static inline float LogPot(float pos) {
        return ((pos < 0.5f) ? (0.2f*pos) : (1.8f*pos - 0.8f));
    }
    
    /**
     * Simulates "W" pot taper
     * Piecewise linear function:
     * (0,0) (0.3,0.1) (0.7,0.9) (1,1)
     */
    static inline float WPot(float pos) {
        if (pos < 0.3f)
            return pos/3.0f;
        else if (pos > 0.7f)
            return (pos/3.0f) + (2.0f/3.0f);
        else
            return pos*2.0f - 0.5f;
    }
    
    /**
     * Calculates RC filter cutoff (in kohms and farads)
     */
    static inline double RcCutoff(double r_kohm, double c_farad) {
        return 1.0 / (M_2_PI * r_kohm * 1000.0 * c_farad);
    }
    
    /**
     * Calculates RC filter cutoff (in kohms and microfarads)
     */
    static inline double RcCutoff_uF(double r_kohm, double c_uFarad) {
        return 1000.0 / (M_2_PI * r_kohm * c_uFarad);
    }
    
    /*
     * Sgn: returns sign of value (-1, 0, or 1)
     */
    template <typename T>
    int Sgn(T val) {
        return (val > static_cast<T>(0)) - (val < static_cast<T>(0));
    }
    
    /*
     * Clipping:
     *
     * Branch-free
     * Will only work for floating-point types
     *
     * Example usage:
     * y = Clip(x, 1.0); // clips x between -1 and 1
     * y = Clip(x, 0.5, 1.0); // clips x between 0.5 and 1
     */
    
    // Symmetric
    template<typename T>
    static inline T Clip(T val, T thresh)
    {
        T const valAbs = std::fabs(val);
        T const clippedAbs = std::min(valAbs, thresh);
        return copysign(clippedAbs, val);
    }
    
    // Asymmetric
    template<typename T>
    static inline T Clip(T val, T minThresh, T maxThresh)
    {
        return std::max(std::min(val, maxThresh), minThresh);
    }
    
    static void Clip(juce::AudioSampleBuffer& buf, float thresh)
    {
        size_t const nSamp = buf.getNumSamples();
        size_t const nChan = buf.getNumChannels();
        
        juce::AudioSampleBuffer tempBuf = buf;
        
        for(uint8_t chan = 0; chan < nChan; ++chan) {
            float* pWriteBuf = buf.getWritePointer(chan);
            float const* pReadBuf = tempBuf.getReadPointer(chan);
            juce::FloatVectorOperations::clip(pWriteBuf, pReadBuf, -thresh, thresh, nSamp);
        }
    }
    static void Clip(juce::AudioSampleBuffer& buf, float minThresh, float maxThresh)
    {
        for(uint8_t chan = 0; chan < buf.getNumChannels(); ++chan) {
            float* pBuf = buf.getWritePointer(chan);
            juce::FloatVectorOperations::clip(pBuf, pBuf, minThresh, maxThresh, buf.getNumSamples());
        }
    }
    
    
    /*
     * Interpolate between val0 and val1
     * by x in range[0,1]
     *
     * Does not check if x is in range - if not, will extrapolate
     *
     * Example usage:
     * y = Interp(10.0, 20.0, 0.5) // returns 15
     */
    template<typename T>
    static inline T Interp(T val0, T val1, T x)
    {
        return ((val1 - val0) * x) + val0;
        
        // Alternative implementation - might be slightly slower
        // likely exactly the same speed
		// however, I think this one is numerically stable and the other might not be
        //return x*val1 + (static_cast<T>(1.0)-x)*val0;
    }

	/*
	 * Takes x in range [min,max], and returns value in range[0,1]
	 */
	template<typename T>
	static inline T ReverseInterp(T min, T max, T x)
	{
		return (x - min) / (max - min);
	}
    
    // in-place
    static void InterpInPlace(float* pVal0Out, float const* pVal1, float x, uint32_t nSamp) {
        juce::FloatVectorOperations::multiply(pVal0Out, 1.0f-x, nSamp);
        juce::FloatVectorOperations::addWithMultiply(pVal0Out, pVal1, x, nSamp);
    }
    
    // out-of-place
    static void Interp(float const* pVal0, float const* pVal1, float* pOut, float x, uint32_t nSamp) {

        // The algorithm below will only work on out-of-place
        // Need to check if trying to make this call in-place
        
        // It's possible that (pVal0 == pVal1), or even (pVal0 == pVal1 == pOut)
        // If so, the Interp calls below should still work
        // Could write special faster code to just copy and/or do nothing, but there's no reason
        // you should normally want to call that, so don't make special behavior.
        
        if (pVal0 == (float const*)pOut) {
            // val0 == out
            // Call in-place on val0
            InterpInPlace(pOut, pVal1, x, nSamp);
            return;
            
        } else if (pVal1 == (float const*)pOut) {
            // val1 == out
            // Call in-place on val1
            InterpInPlace(pOut, pVal0, 1.0f-x, nSamp);
            return;
        }
        
        // As far as I can tell, these two calls do exactly the same thing:
        juce::FloatVectorOperations::copyWithMultiply(pOut, pVal0, 1.0f-x, nSamp);
        //juce::FloatVectorOperations::multiply(pOut, pVal0, 1.0f-x, nSamp);
        
        juce::FloatVectorOperations::addWithMultiply(pOut, pVal1, x, nSamp);
    }
    
    static void Interp(juce::AudioSampleBuffer const& val0, juce::AudioSampleBuffer const& val1, juce::AudioSampleBuffer& outBuf, float x)
    {
        size_t const nChan = outBuf.getNumChannels();
        size_t const nSamp = outBuf.getNumSamples();
        
        DEBUG_ASSERT(size_t(val0.getNumSamples()) == nSamp);
        DEBUG_ASSERT(size_t(val1.getNumSamples()) == nSamp);
        DEBUG_ASSERT(size_t(val0.getNumChannels()) == nChan);
        DEBUG_ASSERT(size_t(val1.getNumChannels()) == nChan);
        
        for(uint8_t chan = 0; chan < nChan; ++chan) {
            Interp(
                   val0.getReadPointer(chan),
                   val1.getReadPointer(chan),
                   outBuf.getWritePointer(chan),
                   x,
                   nSamp);
        }
    }
    
    static void InterpInPlace(juce::AudioSampleBuffer& val0out, juce::AudioSampleBuffer const& val1, float x)
    {
        size_t const nChan = val0out.getNumChannels();
        size_t const nSamp = val0out.getNumSamples();
        
        DEBUG_ASSERT(size_t(val1.getNumSamples()) == nSamp);
        DEBUG_ASSERT(size_t(val1.getNumChannels()) == nChan);
        
        for(uint8_t chan = 0; chan < nChan; ++chan) {
            InterpInPlace(
                   val0out.getWritePointer(chan),
                   val1.getReadPointer(chan),
                   x,
                   nSamp);
        }
    }
    
    static float GenerateSine(float* outBuf, uint32_t nSamp, float freq, float phase = 0.0f) {
        // TODO: compare, see which is faster
#if 1
        // Populate with phase
        for (uint32_t n = 0; n < nSamp; ++n) {
            outBuf[n] = phase;
            phase += freq;
        }
        juce::FloatVectorOperations::multiply(outBuf, float(2.0*M_PI), nSamp);
        
        // Then take sine
        for (uint32_t n = 0; n < nSamp; ++n) {
            outBuf[n] = sinf(outBuf[n]);
        }
#else
        // Do it all in one step
        for (uint32_t n = 0; n < nSamp; ++n) {
            wp[n] = sinf(phase*M_2_PI);
            phase += freq;
        }
#endif
        return phase;
    }
    
    // freq = normalized frequency (cycles per sample, i.e. freq/sampleRate)
    // phase = normalized, 0-1
    // returns phase value
    static float GenerateSine(juce::AudioSampleBuffer& outBuf, float freq, float phase = 0.0f) {
        size_t const nChan = outBuf.getNumChannels();
        size_t const nSamp = outBuf.getNumSamples();
        
        // Generate only on first channel
        float* wp = outBuf.getWritePointer(0);

        phase = GenerateSine(wp, nSamp, freq, phase);
        
        // If multichannel, copy to other channels
        for (uint8_t chan = 1; chan < nChan; ++chan) {
            juce::FloatVectorOperations::copy(outBuf.getWritePointer(chan), outBuf.getReadPointer(0), nSamp);
        }
        
        return phase;
    }

	static float Rms(Buffer const& buf) {
		Buffer squBuf = buf * buf;
		float sum = 0.0f;
		size_t nSamp = buf.GetLength();
		sample_t const* p = squBuf.GetConst();
		for (size_t n = 0; n < nSamp; ++n) sum += p[n];
		return sqrtf(sum / float(nSamp));
	}

	/*
	 * Accumulates frequency buffer (i.e. converts frequency to phase)
	 * Returns starting phase of next buffer
	 */
	static float FreqToPhase(Buffer& buf, float phase) {
		
		float prevFreq;
		float* p = buf.Get();

		for (size_t n = 0; n < buf.GetLength(); ++n) {
			prevFreq = p[n];
			p[n] = phase;
			phase += prevFreq;
			phase = fmod(phase, 1.0f);
		}

		return phase;
	}

	/*
	 * Determines starting phase of next buffer without modifying buffer
	 */
	static float FreqToPhaseNoProcess(Buffer const& buf, float phase) {

		float const* p = buf.GetConst();

		for (size_t n = 0; n < buf.GetLength(); ++n) {
			phase += p[n];
		}

		return fmod(phase, 1.0f);
	}
}

#endif  // DSPUTILS_H_INCLUDED
