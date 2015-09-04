/*
  ==============================================================================

    OnePoleTest.cpp
    Created: 16 Aug 2015 12:32:03pm
    Author:  Joel Geddert

  ==============================================================================
*/

#include "OnePoleTest.h"

#include "Utils/OnePole.h"
#include "Utils/DspUtils.h"

#include "JuceHeader.h"

#include <iostream>
#include <fstream>

namespace Test {

std::string const k_basicTestFilename("OnePole_BasicTest.csv");
std::string const k_freqSweepFilename("OnePole_FreqSweep.csv");

namespace Detail {
    static void BufToCsv(AudioSampleBuffer const& buf, std::string filename) {
        uint32_t const nSamp = buf.getNumSamples();
        uint8_t const nChan = buf.getNumChannels();

        std::cout << "Writing data to file: " << filename << std::endl;

        std::ofstream ofile;
        ofile.open (filename);
        
        for (uint8_t chan = 0; chan < nChan; ++chan) {
            float const* rp = buf.getReadPointer(chan);
            for (uint32_t n = 0; n < nSamp; ++n) {
                ofile << rp[n] << ",";
            }
            ofile << std::endl;
        }
        
        ofile.close();
    }
    
    static float GetRmsPow(float const* pBuf, uint32_t nSamp, uint32_t startSamp) {
        Utils::ScopedFloatBuffer squBuf(nSamp);
        
        float* pSquBuf = squBuf.Get();
        
        juce::FloatVectorOperations::multiply(pSquBuf, pBuf, pBuf, nSamp);
        
        float sumSquPow = 0;
        for (uint32_t n = startSamp; n < nSamp; ++n) {
            sumSquPow += pSquBuf[n];
        }
        
        return sqrt(sumSquPow / float(nSamp - startSamp));
    }
    
    // Convert RMS power to amplitude (ONLY works for sines!)
    static float SinRmsToAmp(float rms) {
        return rms * M_SQRT2;
    }
}

OnePoleTest::OnePoleTest()
    : UnitTest("OnePole test")
{}

void OnePoleTest::runTest() {
    BasicTest_(k_basicTestFilename);
    FreqSweepTest_(k_freqSweepFilename);
}

void OnePoleTest::BasicTest_(std::string filename) {

    beginTest("OnePole basic test");

    // TODO: highpass too

    float const sampleRate = 44100.0f;

    uint32_t const nSamp = 44100;
    
    uint8_t const nFreq = 3;
    float const fc[nFreq] = {20.0f, 440.0f, 5000.0f};

    AudioSampleBuffer buf(3*nFreq, nSamp);

    for (uint8_t f = 0; f < nFreq; ++f) {
        float freq = fc[f] / sampleRate;
		
		Utils::OnePole filt(1, freq);
        
        Utils::GenerateSine(buf.getWritePointer(3*f), nSamp, freq);
        
        filt.ProcessLowpass(buf.getReadPointer(3*f), buf.getWritePointer(3*f+1), nSamp, 0);
        filt.Clear();
        filt.ProcessHighpass(buf.getReadPointer(3*f), buf.getWritePointer(3*f+2), nSamp, 0);
        
        float const in_dB = Utils::AmpTodB(Detail::SinRmsToAmp(Detail::GetRmsPow(buf.getReadPointer(3*f), nSamp, 1000)));
        float const outLp_dB = Utils::AmpTodB(Detail::SinRmsToAmp(Detail::GetRmsPow(buf.getReadPointer(3*f+1), nSamp, 1000)));
        float const outHp_dB = Utils::AmpTodB(Detail::SinRmsToAmp(Detail::GetRmsPow(buf.getReadPointer(3*f+2), nSamp, 1000)));
		float const exp_dB = -3.0f;//in_dB - 3.0f;
        
        bool bEq = Utils::ApproxEqual(outLp_dB, exp_dB, 0.1f);
        bEq &= Utils::ApproxEqual(outHp_dB, exp_dB, 0.1f);
        
        //if (!bEq)
		{
            std::cout << "Freq: " << fc[f] << " Hz (w=" << freq << ")" << std::endl
                      << "    input " << in_dB << " dB, expected output amp " << exp_dB << " dB" << std::endl
                      << "    output LP amp " << outLp_dB << " dB" << std::endl
                      << "    output HP amp " << outHp_dB << " dB" << std::endl;
        }
        
        expect(bEq);
    }
    
    Detail::BufToCsv(buf, filename);
}

void OnePoleTest::FreqSweepTest_(std::string filename) {

    beginTest("OnePole frequency sweep test");

    // TODO: highpass too
    
    float nPeriods = 11.0f;
    
    float const sampleRate = 44100.0f;
    
    float const fc = 1000.0f;
    
    uint8_t const nFreq = 23;
    uint32_t const f[nFreq] = {10, 30, 100, 200, 300, 400, 500, 600, 700, 800, 900,
                            1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,
                            10000, 13000, 20000};
    
    AudioSampleBuffer outBuf(3, nFreq);
    
    float* outFreqs = outBuf.getWritePointer(0);
    float* outPows = outBuf.getWritePointer(1);
    float* outPhases = outBuf.getWritePointer(2);
    
    Utils::OnePole filt(1, fc/sampleRate);
    
    for (uint8_t n = 0; n < nFreq; ++n) {
    
        float const freq = f[n];
    
        // Number of samples = 3 periods
        float period = sampleRate / freq;
        uint32_t const nSamp = std::round(period*nPeriods);
        uint32_t iPeriod = std::round(period);
    
        Utils::ScopedFloatBuffer buf(nSamp);
        float* pBuf = buf.Get();
    
        outFreqs[n] = freq;
    
        filt.Clear();
    
        Utils::GenerateSine(pBuf, nSamp, freq/sampleRate);
        
        filt.ProcessLowpass(pBuf, nSamp, 0);
        
        // Start after first period
        float amp = Detail::SinRmsToAmp(Detail::GetRmsPow(pBuf, nSamp, iPeriod));
        outPows[n] = Utils::AmpTodB(amp);
        
        // TODO: measure phase
    }
    
    Detail::BufToCsv(outBuf, k_freqSweepFilename);
}

} // namespace Test



