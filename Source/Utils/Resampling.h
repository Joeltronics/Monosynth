/*
  ==============================================================================

    Resampling.h
    Created: 4 Aug 2015 8:15:40am
    Author:  Joel Geddert

  ==============================================================================
*/

#ifndef RESAMPLING_H_INCLUDED
#define RESAMPLING_H_INCLUDED

#include "JuceHeader.h"

#include <vector>

namespace  Utils {
    
    // ***** Static functions *****

    void ZeroPadUpsample(AudioSampleBuffer& outBuf, AudioSampleBuffer const& inBuf, uint8_t nUpsamp, bool bScale);
    void NearestUpsample(AudioSampleBuffer& outBuf, AudioSampleBuffer const& inBuf, uint8_t nUpsamp);
    
    void NaiveDownsample(AudioSampleBuffer& outBuf, AudioSampleBuffer const& inBuf, uint8_t nDownsamp, bool bScale);
    void AveragingDownsample(AudioSampleBuffer& outBuf, AudioSampleBuffer const& inBuf, uint8_t nDownsamp, bool bScale);

    static inline void NaiveDownsample(AudioSampleBuffer& outBuf, AudioSampleBuffer const& inBuf, uint8_t nDownsamp)
        { NaiveDownsample(outBuf, inBuf, nDownsamp, false); }
    
    static inline void AveragingDownsample(AudioSampleBuffer& outBuf, AudioSampleBuffer const& inBuf, uint8_t nDownsamp)
        { AveragingDownsample(outBuf, inBuf, nDownsamp, false); }
    
    // ***** Resampling interface *****
    
    // Some of the resampling classes (all the stateless ones) simply call the static
    // functions declared above - the point is that they implement this interface, so
    // they can be drop-in replacements for other resamplers
    
    class IResampler {
    public:
        virtual ~IResampler() {}
        virtual void Process(AudioSampleBuffer const& inBuf, AudioSampleBuffer& outBuf) = 0;
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
        void Process(AudioSampleBuffer const& inBuf, AudioSampleBuffer& outBuf);
        
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
        void Process(AudioSampleBuffer const& inBuf, AudioSampleBuffer& outBuf);
        
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
        LinearInterpUpsampler(uint8_t nUpsamp, uint8_t nChannels);
        LinearInterpUpsampler(uint8_t nUpsamp, uint8_t nChannels, bool bMinGroupDelay);
        ~LinearInterpUpsampler() {}
        void Process(AudioSampleBuffer const& inBuf, AudioSampleBuffer& outBuf);
        
    private:
        void Reset_();
        
        uint8_t const m_nUpsamp;
        uint8_t const m_nChan;
        bool const m_bMinDelay;
        std::vector<float> m_lastSamp;
    };
    
    /**
     * Upsamples by FIR filter (best, but slowest)
     */
    class FirUpsampler : public IResampler {
    public:
        FirUpsampler(uint8_t nUpsamp, uint8_t nChannels, float freq);
        FirUpsampler(uint8_t nUpsamp, uint8_t nChannels);
        ~FirUpsampler() {}
        
        void Process(AudioSampleBuffer const& inBuf, AudioSampleBuffer& outBuf);
        
    private:
        uint8_t const m_nUpsamp;
        uint8_t m_nChan;
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
        NaiveDownsampler(uint8_t nDownsamp) :
            m_nDownsamp(nDownsamp), m_bScale(false) {}
        NaiveDownsampler(uint8_t nDownsamp, bool bScale) :
            m_nDownsamp(nDownsamp), m_bScale(bScale) {}
        ~NaiveDownsampler() {}
        
        // inlined below
        void Process(AudioSampleBuffer const& inBuf, AudioSampleBuffer& outBuf);
        
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
        AveragingDownsampler(uint8_t nDownsamp) :
            m_nDownsamp(nDownsamp), m_bScale(false) {}
        AveragingDownsampler(uint8_t nDownsamp, bool bScale) :
            m_nDownsamp(nDownsamp), m_bScale(bScale) {}
        ~AveragingDownsampler() {}
        
        // inlined below
        void Process(AudioSampleBuffer const& inBuf, AudioSampleBuffer& outBuf);
        
    private:
        uint8_t const m_nDownsamp;
        bool const m_bScale;
    };
    
    /**
     * Downsamples by FIR filter (best, but slowest)
     */
    class FirDownsampler : public IResampler {
    public:
        FirDownsampler(uint8_t nDownsamp, uint8_t nChannels, float freq);
        FirDownsampler(uint8_t nDownsamp, uint8_t nChannels);
        ~FirDownsampler() {}
        
        void Process(AudioSampleBuffer const& inBuf, AudioSampleBuffer& outBuf);
        
    private:
        uint8_t const m_nDownsamp;
        uint8_t m_nChan;
    };
    
    
    inline void ZeroPadUpsampler::Process(AudioSampleBuffer const& inBuf, AudioSampleBuffer& outBuf)
        { ZeroPadUpsample(outBuf, inBuf, m_nUpsamp, m_bScale); }
    
    inline void NearestUpsampler::Process(AudioSampleBuffer const& inBuf, AudioSampleBuffer& outBuf)
        { NearestUpsample(outBuf, inBuf, m_nUpsamp); }
    
    inline void NaiveDownsampler::Process(AudioSampleBuffer const& inBuf, AudioSampleBuffer& outBuf)
        { NaiveDownsample(outBuf, inBuf, m_nDownsamp, m_bScale); }
    
    inline void AveragingDownsampler::Process(AudioSampleBuffer const& inBuf, AudioSampleBuffer& outBuf)
        { AveragingDownsample(outBuf, inBuf, m_nDownsamp, m_bScale); }
    
}



#endif  // RESAMPLING_H_INCLUDED
