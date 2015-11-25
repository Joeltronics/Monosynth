/*
  ==============================================================================

    OnePoleTest.cpp
    Created: 16 Aug 2015 12:32:03pm
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

#include "OnePoleTest.h"

#include "JuceHeader.h"

#include "ResamplingUnitTest.h"

#include "Utils/Utils.h"

#include <iostream>
#include <fstream>

using namespace Utils;

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
        Buffer squBuf(nSamp);
		float* pSquBuf = squBuf.Get();

        juce::FloatVectorOperations::multiply(squBuf.Get(), pBuf, pBuf, nSamp);
        
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
	RiseTimeTest_();
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
		
		Utils::OnePole filt(freq);
        
        Utils::GenerateSine(buf.getWritePointer(3*f), nSamp, freq);
        
        filt.ProcessLowpass(buf.getReadPointer(3*f), buf.getWritePointer(3*f+1), nSamp);
        filt.Clear();
        filt.ProcessHighpass(buf.getReadPointer(3*f), buf.getWritePointer(3*f+2), nSamp);
        
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
    
    Utils::OnePole filt(fc/sampleRate);
    
    for (uint8_t n = 0; n < nFreq; ++n) {
    
        float const freq = f[n];
    
        // Number of samples = 3 periods
        float period = sampleRate / freq;
        uint32_t const nSamp = std::round(period*nPeriods);
        uint32_t iPeriod = std::round(period);
    
        Buffer buf(nSamp);
        float* pBuf = buf.Get();
    
        outFreqs[n] = freq;
    
        filt.Clear();
    
        Utils::GenerateSine(pBuf, nSamp, freq/sampleRate);
        
        filt.ProcessLowpass(pBuf, nSamp);
        
        // Start after first period
        float amp = Detail::SinRmsToAmp(Detail::GetRmsPow(pBuf, nSamp, iPeriod));
        outPows[n] = Utils::AmpTodB(amp);
        
        // TODO: measure phase
    }
    
    Detail::BufToCsv(outBuf, k_freqSweepFilename);
}

void OnePoleTest::RiseTimeTest_() {

	beginTest("Rise time test");

	double sampleRate = 44100.0;
	
	// 0.63212
	sample_t const k_riseVal = sample_t(1.0 - 1.0 / exp(1.0));

	std::vector<double> riseTimes_s;
	riseTimes_s.push_back(0.01);
	riseTimes_s.push_back(0.1);
	riseTimes_s.push_back(1.0);
	riseTimes_s.push_back(10.0);

	Utils::OnePole filt;

	for (auto it = riseTimes_s.begin(); it != riseTimes_s.end(); ++it) {
		
		double riseTime_s = *it;

		// in samples
		size_t riseTime_samp = RoundTo<size_t>(riseTime_s * sampleRate);
		size_t nSamp = 2*riseTime_samp;

		filt.SetRiseTime(riseTime_s, sampleRate);
		filt.Clear();

		size_t measuredRiseTime_samp = 0;

		sample_t opVal;
		sample_t valueAtRiseTime = 0.0f;
		for (size_t n = 0; n < nSamp; ++n)
		{
			opVal = filt.ProcessLowpass(1.0f);

			if (n == riseTime_samp) {
				valueAtRiseTime = opVal;
			}

			if (opVal > k_riseVal) {
				measuredRiseTime_samp = n;
				break;
			}
		}

		size_t marginOfError = size_t(std::ceil( double(riseTime_samp) * 0.1 ));

		size_t minRiseTime_samp = riseTime_samp - marginOfError;
		size_t maxRiseTime_samp = riseTime_samp + marginOfError;

		if (measuredRiseTime_samp) {
			if (measuredRiseTime_samp < minRiseTime_samp || measuredRiseTime_samp > maxRiseTime_samp)
			{
				std::cout << "ERROR: rise time " << measuredRiseTime_samp << ", expected " << riseTime_samp
					<< " (range " << minRiseTime_samp << " to " << maxRiseTime_samp << ")" << std::endl;
			}

			if (!Utils::ApproxEqual(valueAtRiseTime, k_riseVal, 0.01f))
			{
				std::cout << "ERROR: value at rise time " << valueAtRiseTime << ", expected " << k_riseVal << std::endl;
			}
		}
		else {
			std::cout << "ERROR: never hit rise time " << riseTime_samp << " samples final value " << opVal << std::endl;
		}

		expect(measuredRiseTime_samp > minRiseTime_samp && measuredRiseTime_samp < maxRiseTime_samp);
		expect(Utils::ApproxEqual(valueAtRiseTime, k_riseVal, 0.01f));
	}
	

}

} // namespace Test



