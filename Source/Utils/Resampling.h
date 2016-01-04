/*
  ==============================================================================

    Resampling.h
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

#ifndef RESAMPLING_H_INCLUDED
#define RESAMPLING_H_INCLUDED

#include "Buffer.h"

#include <vector>

namespace IirCoeffs {
#include "DownsamplingIirCoeffs.h"
}

namespace  Utils {
    
    // ***** Static functions *****

    void ZeroPadUpsample(Buffer& outBuf, Buffer const& inBuf, uint8_t nUpsamp, bool bScale);
    void NearestUpsample(Buffer& outBuf, Buffer const& inBuf, uint8_t nUpsamp);
    
    void NaiveDownsample(Buffer& outBuf, Buffer const& inBuf, uint8_t nDownsamp, bool bScale = false);
    void AveragingDownsample(Buffer& outBuf, Buffer const& inBuf, uint8_t nDownsamp, bool bScale = false);
    
    // ***** Resampling interface *****
    
    // Some of the resampling classes (all the stateless ones) simply call the static
    // functions declared above - the point is that they implement this interface, so
    // they can be drop-in replacements for other resamplers
    
    class IResampler {
    public:
        virtual ~IResampler() {}
        virtual void Process(Buffer& outBuf, Buffer const& inBuf) = 0;
		virtual void Clear() {};
    };
    
    // ***** Upsamplers *****
    
    /**
     * Upsamples by filling in the gaps with zeros
     * bScale = multiply by N (to maintain same mean signal amplitude)
     *
     * Stateless
     */
    class ZeroPadUpsampler : public IResampler {
    public:
        ZeroPadUpsampler(uint8_t nUpsamp, bool bScale) :
            m_nUpsamp(nUpsamp), m_bScale(bScale) {}
        ~ZeroPadUpsampler() {}
        
        // inlined below
        void Process(Buffer& outBuf, Buffer const& inBuf) override;
        
    private:
        uint8_t const m_nUpsamp;
        bool const m_bScale;
    };
    
    /**
     * Upsamples by repeating each sample
     *
     * Stateless
     */
    class NearestUpsampler : public IResampler {
    public:
        NearestUpsampler(uint8_t nUpsamp) :
            m_nUpsamp(nUpsamp) {}
        ~NearestUpsampler() {}
        
        // inlined below
        void Process(Buffer& outBuf, Buffer const& inBuf) override;
        
    private:
        uint8_t const m_nUpsamp;
    };
    
    /**
     * Upsamples using linear interpolation
     *
     * By default, has 1 (input) sample group delay
     * If bMinGroupDelay = true, has slightly less group delay (1 *output* sample less)
     * The problem is this is no longer integer of input samples
     * e.g. if upsampling by 4, would have 0.75 input samples (3 output samples) group delay
     */
    class LinearInterpUpsampler : public IResampler {
    public:
        LinearInterpUpsampler(uint8_t nUpsamp, uint8_t nChannels, bool bMinGroupDelay = false);
        ~LinearInterpUpsampler() {}
        void Process(Buffer& outBuf, Buffer const& inBuf) override;
        
    private:
        void Reset_();
        
        uint8_t const m_nUpsamp;
        uint8_t const m_nChan;
        bool const m_bMinDelay;
        sample_t m_lastSamp;
    };
     
    // ***** Downsamplers *****
    
    /**
     * Just takes every nth sample and ignores the ones in between
     * Low quality, but will work fine if you already know there is no content above new Nyquist
     * (e.g. if you've already filtered)
     *
     * bScale = multiply by N
     *
     * Stateless
     */
    class NaiveDownsampler : public IResampler {
    public:
        NaiveDownsampler(uint8_t nDownsamp, bool bScale = false) :
            m_nDownsamp(nDownsamp), m_bScale(bScale) {}
        ~NaiveDownsampler() {}
        
        // inlined below
        void Process(Buffer& outBuf, Buffer const& inBuf) override;
        
    private:
        uint8_t const m_nDownsamp;
        bool const m_bScale;
    };
    
    /**
     * Downsamples by taking average of n samples (equivalent to rolling mean filter of size n)
     * bScale = multiply by N
     *
     * Stateless
     */
    class AveragingDownsampler : public IResampler {
    public:
        AveragingDownsampler(uint8_t nDownsamp, bool bScale = false) :
            m_nDownsamp(nDownsamp), m_bScale(bScale) {}
        ~AveragingDownsampler() {}
        
        // inlined below
        void Process(Buffer& outBuf, Buffer const& inBuf) override;
        
    private:
        uint8_t const m_nDownsamp;
        bool const m_bScale;
    };

	// ***** IIR Downsamplers *****
	// (Defined in DownsamplingIir.cpp)

	/*
	These should work very well for resampling from 176.4 kHz and 192 kHz, with almost no
	aliasing below 20 kHz (max -83 dB, but realistically even less)

	The catches:
	- they're not that efficient (6-10 order IIR filters running at the higher sample rate)
	- they're not linear-phase

	These could possibly be vectorized, though vectorizing an IIR filter is black magic
	*/

	// 176.4 kHz ---4x--> 44.1 kHz
	class IirDownsampler_176_44 : public IResampler {
	public:
		IirDownsampler_176_44();
		~IirDownsampler_176_44() {}
		void Process(Buffer& outBuf, Buffer const& inBuf) override;
		void Clear() override;

	private:
		static const size_t nResamp = 4;
		static const size_t order = IirCoeffs::order_176_44;
		static const size_t nBiquad = IirCoeffs::nBiquad_176_44;
		sample_t z[order];
	};

	// 192 kHz ---4x--> 48 kHz
	class IirDownsampler_192_48 : public IResampler {
	public:
		IirDownsampler_192_48();
		~IirDownsampler_192_48() {}
		void Process(Buffer& outBuf, Buffer const& inBuf) override;
		void Clear() override;

	private:
		static const size_t nResamp = 4;
		static const size_t order = IirCoeffs::order_192_48;
		static const size_t nBiquad = IirCoeffs::nBiquad_192_48;
		sample_t z[order];
	};

	// 176.4 kHz ---2x--> 88.2 kHz
	class IirDownsampler_176_88 : public IResampler {
	public:
		IirDownsampler_176_88();
		~IirDownsampler_176_88() {}
		void Process(Buffer& outBuf, Buffer const& inBuf) override;
		void Clear() override;

	private:
		static const size_t nResamp = 2;
		static const size_t order = IirCoeffs::order_176_88;
		static const size_t nBiquad = IirCoeffs::nBiquad_176_88;
		sample_t z[order];
	};

	// 192 kHz ---2x--> 96 kHz
	class IirDownsampler_192_96 : public IResampler {
	public:
		IirDownsampler_192_96();
		~IirDownsampler_192_96() {}
		void Process(Buffer& outBuf, Buffer const& inBuf) override;
		void Clear() override;

	private:
		static const size_t nResamp = 2;
		static const size_t order = IirCoeffs::order_192_96;
		static const size_t nBiquad = IirCoeffs::nBiquad_192_96;
		sample_t z[order];
	};
    
	// ***** Inline Functions *****

	inline void ZeroPadUpsampler::Process(Buffer& outBuf, Buffer const& inBuf)
        { ZeroPadUpsample(outBuf, inBuf, m_nUpsamp, m_bScale); }
    
    inline void NearestUpsampler::Process(Buffer& outBuf, Buffer const& inBuf)
        { NearestUpsample(outBuf, inBuf, m_nUpsamp); }
    
    inline void NaiveDownsampler::Process(Buffer& outBuf, Buffer const& inBuf)
        { NaiveDownsample(outBuf, inBuf, m_nDownsamp, m_bScale); }
    
    inline void AveragingDownsampler::Process(Buffer& outBuf, Buffer const& inBuf)
        { AveragingDownsample(outBuf, inBuf, m_nDownsamp, m_bScale); }
    
}

#endif  // RESAMPLING_H_INCLUDED
