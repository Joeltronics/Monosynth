/*
  ==============================================================================

    ResamplingTest.cpp
    Created: 4 Aug 2015 11:07:36pm
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

#include "ResamplingUnitTest.h"

#include "JuceHeader.h"

#include "Utils/Utils.h"

#include <utility>
typedef std::pair<float, float> floatPair;

using namespace Utils;

namespace Detail {
	
	static float CalcAliasedFreq(float freq, float sampleRate) {
		double wn = freq / sampleRate;
		wn = fmod(wn, 1.0);
		if (wn < 0.0) wn += 1.0;
		if (wn > 0.5) wn = 1.0 - wn;
		return float(wn * double(sampleRate));
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

	static float GetSinAmpdB(Buffer const& buf, size_t startSamp) {
		float rms = Detail::GetRmsPow(buf.GetConst(), buf.GetLength(), startSamp);
		float amp = Detail::SinRmsToAmp(rms);
		float dB = Utils::AmpTodB(amp);
		return dB;
	}
}

namespace Test {

ResamplingUnitTest::ResamplingUnitTest()
: UnitTest("Resampling unit test")
{}

static inline bool CheckEquals_(Buffer const& actual, Buffer const& expected) {

    DEBUG_ASSERT(actual.GetLength() == expected.GetLength());

    uint32_t const nSamp = expected.GetLength();
    bool bEq = true;
    if (!Utils::ApproxEqual(actual, expected)) {
        bEq = false;
        std::cout << "Not equal!" << std::endl;
        std::cout << "Values:   ";
        for (uint8_t n = 0; n < nSamp; ++n) {
            std::cout << actual.GetConst()[n] << " ";
        }
        std::cout << std::endl;
        std::cout << "Expected: ";
        for (uint8_t n = 0; n < nSamp; ++n) {
            std::cout << expected.GetConst()[n] << " ";
        }
        std::cout << std::endl;
    }
    
    return bEq;
}
    
void ResamplingUnitTest::runTest()
{
    juce::ScopedPointer<IResampler> pResamp;

	// Basic Upsamplers
    {
		Buffer inBuf0(4);
		Buffer inBuf1(4);
        Buffer outBuf(16);
        
        float const inValsUp0[4] = {1.0f, -2.3f, -0.0f, 0.3f};
        float const inValsUp1[4] = {0.1f, 3.2f, -600.0f, 2.1f};

		juce::FloatVectorOperations::copy(inBuf0.Get(), inValsUp0, 4);
		juce::FloatVectorOperations::copy(inBuf1.Get(), inValsUp1, 4);

        beginTest("Testing ZeroPadUpsampler");
        {
            float expVals0[16] = { 1.0f, 0.0f, 0.0f, 0.0f, -2.3f, 0.0f, 0.0f, 0.0f,   -0.0f, 0.0f, 0.0f, 0.0f, 0.3f, 0.0f, 0.0f, 0.0f };
			float expVals1[16] = { 0.1f, 0.0f, 0.0f, 0.0f, 3.2f,  0.0f, 0.0f, 0.0f, -600.0f, 0.0f, 0.0f, 0.0f, 2.1f, 0.0f, 0.0f, 0.0f };
            
			pResamp = new Utils::ZeroPadUpsampler(4, false);
            pResamp->Process(outBuf, inBuf0);
			expect(CheckEquals_(outBuf, Buffer(expVals0, 16)));
            
			pResamp = new Utils::ZeroPadUpsampler(4, false);
			pResamp->Process(outBuf, inBuf1);
			expect(CheckEquals_(outBuf, Buffer(expVals1, 16)));

			juce::FloatVectorOperations::multiply(expVals0, 4.0f, 16);
			juce::FloatVectorOperations::multiply(expVals1, 4.0f, 16);

            pResamp = new Utils::ZeroPadUpsampler(4, true);
			pResamp->Process(outBuf, inBuf0);
			expect(CheckEquals_(outBuf, Buffer(expVals0, 16)));

			pResamp = new Utils::ZeroPadUpsampler(4, true);
			pResamp->Process(outBuf, inBuf1);
			expect(CheckEquals_(outBuf, Buffer(expVals1, 16)));
        }
        
        beginTest("Testing NearestUpsampler");
        {
			float expVals0[16] = { 1.0f, 1.0f, 1.0f, 1.0f, -2.3f, -2.3f, -2.3f, -2.3f,   -0.0f, -0.0f, -0.0f, -0.0f, 0.3f, 0.3f, 0.3f, 0.3f };
			float expVals1[16] = { 0.1f, 0.1f, 0.1f, 0.1f,  3.2f,  3.2f,  3.2f,  3.2f, -600.0f, -600.0f, -600.0f, -600.0f, 2.1f, 2.1f, 2.1f, 2.1f };

            pResamp = new Utils::NearestUpsampler(4);
			pResamp->Process(outBuf, inBuf0);
			expect(CheckEquals_(outBuf, Buffer(expVals0, 16)));

			pResamp = new Utils::NearestUpsampler(4);
			pResamp->Process(outBuf, inBuf1);
			expect(CheckEquals_(outBuf, Buffer(expVals1, 16)));
        }
        
        beginTest("Testing LinearInterpUpsampler");
        {
            {
				float expVals0[16] = { 0.0f, 0.25f, 0.50f, 0.75f, 1.0f, 0.175f, -0.65f, -1.475f, -2.3f, -1.725f, -1.15f, -0.575f, 0.0f, 0.075f, 0.15f, 0.225f };
				float expVals1[16] = { 0.0f, 0.025f, 0.05f, 0.075f, 0.1f, 0.875f, 1.65f, 2.425f, 3.2f, -147.6f, -298.4f, -449.2f, -600.0f, -449.475f, -298.95f, -148.425f };

                pResamp = new Utils::LinearInterpUpsampler(4, 2, false);
				pResamp->Process(outBuf, inBuf0);
                expect(CheckEquals_(outBuf, Buffer(expVals0, 16)));
				
				pResamp = new Utils::LinearInterpUpsampler(4, 2, false);
				pResamp->Process(outBuf, inBuf1);
				expect(CheckEquals_(outBuf, Buffer(expVals1, 16)));
            }
        
            {
				float expVals0[16] = { 0.25f, 0.50f, 0.75f, 1.0f, 0.175f, -0.65f, -1.475f, -2.3f, -1.725f, -1.15f, -0.575f, 0.0f, 0.075f, 0.15f, 0.225f, 0.3f };
				float expVals1[16] = { 0.025f, 0.05f, 0.075f, 0.1f, 0.875f, 1.65f, 2.425f, 3.2f, -147.6f, -298.4f, -449.2f, -600.0f, -449.475f, -298.95f, -148.425f, 2.1f };

                pResamp = new Utils::LinearInterpUpsampler(4, 2, true);
				pResamp->Process(outBuf, inBuf0);
                expect(CheckEquals_(outBuf, Buffer(expVals0, 16)));

				pResamp = new Utils::LinearInterpUpsampler(4, 2, true);
				pResamp->Process(outBuf, inBuf1);
				expect(CheckEquals_(outBuf, Buffer(expVals1, 16)));
            }
        }
    }
    
	// Basic Downsamplers
    {
        Buffer inBuf0(16);
		Buffer inBuf1(16);
        
        float const inValsDown0[16] = {1.0f, -2.3f, -0.0f, 0.3f, 4.1f, -200.0f, 3.14f, 2.71f, -6.0f, 4.2f, 0.01f, -10.0f, -0.0f, 512.0f, -2.1f, 6.0f};
        float const inValsDown1[16] = {0.1f, 3.2f, -600.0f, 2.1f, 3.14f, -1.0f, 6.2f, -7.0f, 1.1f, 1.2f, 1.3f, 1.4f, 1.5f, -1.5f, 4.01f, 2.2f};
        juce::FloatVectorOperations::copy(inBuf0.Get(), inValsDown0, 16);
        juce::FloatVectorOperations::copy(inBuf1.Get(), inValsDown1, 16);
        
        beginTest("Testing NaiveDownsampler");
        {
            Buffer outBuf(2, 4);
        
            float expVals0[4] = {inValsDown0[0], inValsDown0[4], inValsDown0[8], inValsDown0[12]};
            float expVals1[4] = {inValsDown1[0], inValsDown1[4], inValsDown1[8], inValsDown1[12]};
            
            pResamp = new Utils::NaiveDownsampler(4);
			pResamp->Process(outBuf, inBuf0);
            expect(CheckEquals_(outBuf, Buffer(expVals0, 4)));

			pResamp = new Utils::NaiveDownsampler(4);
			pResamp->Process(outBuf, inBuf1);
			expect(CheckEquals_(outBuf, Buffer(expVals1, 4)));

            juce::FloatVectorOperations::multiply(expVals0, 4.0f, 4);
            juce::FloatVectorOperations::multiply(expVals1, 4.0f, 4);
            
            pResamp = new Utils::NaiveDownsampler(4, true);
			pResamp->Process(outBuf, inBuf0);
			expect(CheckEquals_(outBuf, Buffer(expVals0, 4)));

			pResamp = new Utils::NaiveDownsampler(4, true);
			pResamp->Process(outBuf, inBuf1);
			expect(CheckEquals_(outBuf, Buffer(expVals1, 4)));
        }
        
        beginTest("Testing AveragingDownsampler");
        {
            Buffer outBuf(4);
        
            #define AVG4(X, N) (X[N] + X[N+1] + X[N+2] + X[N+3]) / 4.0f
            #define AVG4x4(X) {AVG4(X,0), AVG4(X,4), AVG4(X,8), AVG4(X,12)}
        
            float expVals0[4] = AVG4x4(inValsDown0);
            float expVals1[4] = AVG4x4(inValsDown1);

            #undef AVG4
            #undef AVG4x4
            
            pResamp = new Utils::AveragingDownsampler(4);
			pResamp->Process(outBuf, inBuf0);
            expect(CheckEquals_(outBuf, Buffer(expVals0, 4)));
			
			pResamp = new Utils::AveragingDownsampler(4);
			pResamp->Process(outBuf, inBuf1);
			expect(CheckEquals_(outBuf, Buffer(expVals1, 4)));
        }
	}
	
	// IIR Downsamplers
	/*
	These tests fail. I'm not sure why.
	
	I suspect it's an error in measuring the sine amplitude, but it's also
	possible there's a problem with the filter itself - either something's
	wrong with the filter design, or it's a digital precision issue, or it's
	a good-ol' bug in the IIR downsamplers.
	
	I'm guessing it's not a precision issue, because if so, I suspect the
	high-order version would perform much worse than the cascaded-biquad
	version, and they actually do quite similarly.
	*/
	{
		size_t const nSamp = 65536;
		Buffer buf(nSamp);
		
		std::vector<float> const freqs = {
			100.f, 440.f, 1000.f, 3000.f, 10000.f, 20000.f, // Audible freqs
			22000.f, 24100.f, 28000.f,
			40e3f, 47e3f, 49e3f, 60e3f,
			68.2e3f, 76e3f, // Will alias to 20 kHz at 44.1 and 48, respectively
			80e3f, 88.1e3f, 90e3f, 95.9e3f
		};

		for (size_t n = 0; n < 4; ++n) {

			juce::String testName;
			float sampleRate;
			size_t nResamp;

			switch (n) {
			case 0:
				pResamp = new Utils::IirDownsampler_176_44();
				testName = "Testing IIR resampler 176.4 kHz -> 44.1 kHz";
				sampleRate = 176400.f;
				nResamp = 4;
				break;
			case 1:
				pResamp = new Utils::IirDownsampler_192_48();
				testName = "Testing IIR resampler 192 kHz -> 48 kHz";
				sampleRate = 192000.f;
				nResamp = 4;
				break;
			case 2:
				pResamp = new Utils::IirDownsampler_176_88();
				testName = "Testing IIR resampler 176.4 kHz -> 88.2 kHz";
				sampleRate = 176400.f;
				nResamp = 2;
				break;
			case 3:
				pResamp = new Utils::IirDownsampler_192_96();
				testName = "Testing IIR resampler 192 kHz -> 96 kHz";
				sampleRate = 192000.f;
				nResamp = 2;
				break;
			default:
				std::cout << "ERROR: n out of bounds\n";
				expect(false);
			}

			
			beginTest(testName);

			Buffer downBuf(nSamp / nResamp);

			std::vector<floatPair> results;

			sample_t phase = 0.f;
			for (auto it = freqs.begin(); it != freqs.end(); ++it) {

				float f = *it;

				float w = f / sampleRate;

				if (w > 0.5f) break;

				phase = GenerateSine(buf, w, phase);

				downBuf.Clear(); // Shouldn't be necessary?

				pResamp->Process(downBuf, buf);

				float ampl = Detail::GetSinAmpdB(downBuf, 1000);
				results.push_back(floatPair(f, ampl));
			}

			float const passbandFailThresh = 0.75f;
			float const aliasFailThresh = -60.0f;
			float maxPassbandError = 0.0f;
			float maxAlias = -99999.9f;

			for (auto it = results.begin(); it != results.end(); ++it) {
				float const inFreq = it->first;
				float const finalFreq = Detail::CalcAliasedFreq(inFreq, sampleRate/nResamp);
				bool const bAlias = !Utils::ApproxEqual(inFreq, finalFreq, 1.0f);
				
				float const ampl = it->second;

				if (inFreq <= 20001.f) {
					maxPassbandError = std::max(maxPassbandError, abs(ampl));
					std::cout << "Audible:    " << inFreq << ", ampl: " << ampl << " dB\n";
				}
				else if (finalFreq <= 20001.f) {
					maxAlias = std::max(maxAlias, ampl);
					std::cout << "Alias:      " << inFreq << " => " << finalFreq << ", ampl: " << ampl << " dB\n";
				}
				else {
					// Don't care about value, but print
					if (!bAlias) {
						std::cout << "Transition: " << inFreq << ", ampl: " << ampl << " dB\n";
					} 
					else {
						std::cout << "Transition: " << inFreq << " => " << finalFreq << ", ampl: " << ampl << " dB\n";
					}
				}
			}

			if (maxPassbandError > passbandFailThresh)
				std::cout << "Fail: max passband error " << maxPassbandError << " dB\n";

			expect(maxPassbandError <= passbandFailThresh);

			if (maxAlias > aliasFailThresh)
				std::cout << "Fail: max aliasing " << maxAlias << " dB\n";

			expect(maxAlias <= aliasFailThresh);
		}
    }
}

} // namespace Test