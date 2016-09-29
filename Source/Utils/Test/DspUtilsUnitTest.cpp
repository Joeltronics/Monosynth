/*
  ==============================================================================

    DspUtilsUnitTest.cpp
    Created: 1 Aug 2015 6:16:04pm
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

#include "JuceHeader.h"

#include "DspUtilsUnitTest.h"

#include "ResamplingUnitTest.h"
#include "Utils/Utils.h"

#include <ctime>

namespace Test {
    
	std::clock_t startTime;

	double TimerDiff(std::clock_t endTime) {
		return double(endTime - startTime) / double(CLOCKS_PER_SEC);
	}

	void __forceinline StartTimer() {
		startTime = std::clock();
	}

	double __forceinline StopTimer() {
		std::clock_t endTime = std::clock();
		return TimerDiff(endTime);
	}

    static bool ApproxEqualTest(double x, double y, bool expected) {
        bool passed = true;
        
        bool ret = Utils::ApproxEqual(x, y);
        if (ret != expected) {
            std::cout << "ApproxEqual<double>(" << x << "," << y << ") expected " << expected << ", returned " << ret << std::endl;
            passed = false;
        }
        
        ret = Utils::ApproxEqual(static_cast<float>(x),static_cast<float>(y));
        if (ret != expected) {
            std::cout << "ApproxEqual<float>(" << x << "," << y << ") expected " << expected << ", returned " << ret << std::endl;
            passed = false;
        }
        
        return passed;
    }
    
    static bool ApproxEqualTest(double x, double y, double tol, bool expected) {
        bool passed = true;
        
        bool ret = Utils::ApproxEqual(x, y, tol);
        if (ret != expected) {
            std::cout << "ApproxEqual<double>("<< x <<","<< y <<","<< tol <<") expected "<< expected <<", returned "<< ret << std::endl;
            passed = false;
        }
        
        ret = Utils::ApproxEqual(static_cast<float>(x),static_cast<float>(y), static_cast<float>(tol));
        if (ret != expected) {
            std::cout << "ApproxEqual<float>("<< x <<","<< y <<","<< tol <<") expected "<< expected <<", returned "<< ret << std::endl;
            passed = false;
        }
        
        return passed;
    }
    
    static bool ClipTest(double x, double thresh, double expected) {
        bool passed = true;
        
        float ret = Utils::Clip<double>(x, thresh);
        if (ret != expected) {
            std::cout << "Clip<double>("<< x <<","<< thresh <<") expected "<< expected <<", returned "<< ret << std::endl;
            passed = false;
        }
        
        ret = Utils::Clip<float>(static_cast<float>(x), static_cast<float>(thresh));
        if (ret != expected) {
            std::cout << "Clip<float>("<< x <<","<< thresh <<") expected "<< expected <<", returned "<< ret << std::endl;
            passed = false;
        }
        
        return passed;
    }
    
    static bool ClipTest(double x, double minThresh, double maxThresh, double expected) {
        bool passed = true;
        
        double dRet = Utils::Clip<double>(x, minThresh, maxThresh);
        if (dRet != expected) {
            std::cout << "Clip<double>("<< x <<","<< minThresh <<","<< maxThresh <<") expected "<< expected <<", returned "<< dRet << std::endl;
            passed = false;
        }
        
        float fRet = Utils::Clip<float>(static_cast<float>(x), static_cast<float>(minThresh), static_cast<float>(maxThresh));
        if (fRet != expected) {
            std::cout << "Clip<float>("<< x <<","<< minThresh <<","<< maxThresh <<") expected "<< expected <<", returned "<< fRet << std::endl;
            passed = false;
        }
        
        return passed;
    }
    
    static bool InterpTest(double v0, double v1, double x, double expected) {
        bool passed = true;
        
        double dRet = Utils::Interp<double>(v0, v1, x);
        if (!Utils::ApproxEqual(dRet, expected)) {
            passed = false;
            std::cout << "Interp<double>("<< v0 <<","<< v1 <<","<< x <<") returned "<< dRet <<", expected " << expected << std::endl;
        }
        
        float fRet = Utils::Interp<float>(v0, v1, x);
        if (!Utils::ApproxEqual(fRet, float(expected))) {
            passed = false;
            std::cout << "Interp<float>("<< v0 <<","<< v1 <<","<< x <<") returned "<< fRet <<", expected " << expected << std::endl;
        }
        
        return passed;
    }

    DspUtilsUnitTest::DspUtilsUnitTest()
    : UnitTest("DspUtils unit test")
    {}
    
    void DspUtilsUnitTest::runTest()
    {
        beginTest("Testing ApproxEqual()");
        {
            expect(ApproxEqualTest(0.0, 0.0, true));
            expect(ApproxEqualTest(0.0, -0.0, true));
            expect(ApproxEqualTest(0.0, 1.0, false));
            expect(ApproxEqualTest(0.0, -1.0, false));
            expect(ApproxEqualTest(0.0, 1.0, 0.9, false));
            expect(ApproxEqualTest(0.0, 1.0, 2.0, true));
            expect(ApproxEqualTest(0.333333, 0.333334, true));
            expect(ApproxEqualTest(0.333, 0.334, 0.0001, false));
        }
        
        beginTest("Testing buffer ApproxEqual()");
        {
            float in1[4] = {1.0f, -0.0f, -7.2f, 1.333f};
            float in2[4] = {1.0f,  0.0f, -7.2f, 1.334f};
            float in3[4] = {1.2f, -0.1f, -7.1f, 1.23f};

            expect(!Utils::ApproxEqual(in1, in2, 4));
            expect(Utils::ApproxEqual(in1, in2, 0.01, 4));
            
            juce::AudioSampleBuffer buf1(2,4);
            juce::AudioSampleBuffer buf2(2,4);
            juce::AudioSampleBuffer buf3(2,4);
            
            juce::FloatVectorOperations::copy(buf1.getWritePointer(0), in1, 4);
            juce::FloatVectorOperations::copy(buf1.getWritePointer(1), in2, 4);
            
            juce::FloatVectorOperations::copy(buf2.getWritePointer(0), in2, 4);
            juce::FloatVectorOperations::copy(buf2.getWritePointer(1), in1, 4);
            
            juce::FloatVectorOperations::copy(buf3.getWritePointer(0), in3, 4);
            juce::FloatVectorOperations::copy(buf3.getWritePointer(1), in2, 4);
            
            expect(Utils::ApproxEqual(buf1, buf2, 0.01));
            expect(!Utils::ApproxEqual(buf1, buf2));
            expect(Utils::ApproxEqual(buf1, buf3, 1.0));
            expect(!Utils::ApproxEqual(buf1, buf3));
            expect(!Utils::ApproxEqual(buf2, buf3));
        }
        
#if 0
		// FIXME: this test is bad! It segfaults in release builds!
        beginTest("Testing CopyAudioSampleBuffer()");
        {
            uint32_t const nSamp = 32;
            uint8_t const nChan = 4;
        
            float data[nChan][nSamp];
            
            juce::AudioSampleBuffer inBuf(nChan, nSamp);
            juce::AudioSampleBuffer outBuf(nChan, nSamp);
            
            for(uint8_t chan = 0; chan < nChan; ++chan) {
                for(uint32_t n = 0; n < nSamp; ++n)
                    data[chan][n] = float(rand()) / float(RAND_MAX);
                
                juce::FloatVectorOperations::copy(inBuf.getWritePointer(chan), data[chan], nSamp);
            }
            
            Utils::CopyAudioSampleBuffer(inBuf, outBuf);
            
            // Test that it wasn't a shallow copy
            for (uint8_t chan = 0; chan < nChan; ++chan)
                expect(inBuf.getReadPointer(chan) != outBuf.getReadPointer(chan));
            
            // Test that the two are equal
            expect(Utils::ApproxEqual(inBuf, outBuf));
        }
#endif
        
        beginTest("Testing Conversions");
        {
            expect(Utils::ApproxEqual(Utils::AmpTodB(0.00316f), -50.0f, 0.01f));
            expect(Utils::ApproxEqual(Utils::AmpTodB(1.0f), 0.0f));
            expect(Utils::ApproxEqual(Utils::AmpTodB(50.0f), 33.979f, 0.01f));
            
            expect(Utils::ApproxEqual(Utils::dBtoAmp(-50.0f), 0.00316f, 0.01f));
            expect(Utils::ApproxEqual(Utils::dBtoAmp(0.0f), 1.0f));
            expect(Utils::ApproxEqual(Utils::dBtoAmp(33.979f), 50.0f, 0.01f));

            expect(Utils::ApproxEqual(Utils::AmpTodB(1.0f), Utils::PowTodB(1.0f)));
            expect(Utils::ApproxEqual(Utils::AmpTodB(float(M_SQRT1_2)), Utils::PowTodB(0.5f)));
            
            expect(Utils::ApproxEqual(Utils::dBtoAmp(15.0f), Utils::dBtoPow(7.5f)));

			expect(Utils::ApproxEqual(Utils::PitchToFreqHz<float>(69.0f), 440.0f));
			expect(Utils::ApproxEqual(Utils::PitchToFreqHz<double>(69.0f), 440.0));
			expect(Utils::ApproxEqual(Utils::PitchToFreqHz<double>(69.0), 440.0));
			expect(Utils::ApproxEqual(Utils::PitchToFreqHz<float>(60.0f), 261.63f, 0.01f));
			expect(Utils::ApproxEqual(Utils::PitchToFreqHz<float>(81.0f), 880.0f));
        }
        
        beginTest("Testing Sgn()");
        {
            expectEquals(Utils::Sgn<float>(55783.3148f), 1);
            expectEquals(Utils::Sgn<double>(1.0), 1);
            expectEquals(Utils::Sgn<float>(1.0f), 1);
            expectEquals(Utils::Sgn<float>(0.00001f), 1);
            expectEquals(Utils::Sgn<float>(0.0f), 0);
            expectEquals(Utils::Sgn<double>(0.0f), 0);
            expectEquals(Utils::Sgn<float>(-0.0f), 0);
            expectEquals(Utils::Sgn<double>(-0.0f), 0);
            expectEquals(Utils::Sgn<float>(-0.00001f), -1);
            expectEquals(Utils::Sgn<float>(-1.0f), -1);
            expectEquals(Utils::Sgn<double>(-458936.3547f), -1);

            expectEquals(Utils::Sgn<int32_t>(55783), 1);
            expectEquals(Utils::Sgn<int32_t>(0), 0);
            expectEquals(Utils::Sgn<int32_t>(-458936), -1);
            
            expectEquals(Utils::Sgn<uint32_t>(5783), 1);
            expectEquals(Utils::Sgn<uint32_t>(0), 0);
            expectEquals(Utils::Sgn<uint32_t>(-123), 1); // unsigned special case
        }
        
        beginTest("Testing Clip()");
        {
            expect(ClipTest(-0.0, 1.0, 0.0));
            expect(ClipTest(1.5, 1.0, 1.0));
            expect(ClipTest(-0.5, 1.0, -0.5));
            expect(ClipTest(-1.5, 1.0, -1.0));
            
            expect(ClipTest(-1.5, 0.5, 1.0, 0.5));
            expect(ClipTest(-1.5, -2.0, 0.0, -1.5));
            expect(ClipTest(0.5, -2.0, -0.0, 0.0));
        }
        
        beginTest("Testing single-sample Interp()");
        {
            expect(InterpTest(0.0, 1.0, 0.5, 0.5));
            expect(InterpTest(-1.0, 1.0, 0.625, 0.25));
            expect(InterpTest(0.0, 2.0, -1.75, -3.5));
            expect(InterpTest(0.0, -2.0, 0.25, -0.5));
            
            // Now test with some random values
            for(uint8_t n = 0; n < 10; ++n) {
                float interpVal = float(rand()) / float(RAND_MAX);
                float v0 = float(rand()) / float(RAND_MAX);
                float v1 = float(rand()) / float(RAND_MAX);
                
                v0 = v0*2.0 - 1.0;
                v1 = v1*2.0 - 1.0;
                
                float y0 = (v1 - v0) * interpVal + v0;
                
                expect(InterpTest(v0, v1, interpVal, y0));
            }
        }
        
        beginTest("Testing AudioSampleBuffer Interp()");
        {
            size_t const nSamp = 8;
            
            float const interpVal = 0.75f;
            
            float inVals0_0[nSamp] = {0.00f, -1.0f, 0.000f, 2.0f };
            float inVals1_0[nSamp] = {1.00f,  1.0f, 0.300f, 0.0f };
            float outVals0[nSamp]  = {0.75f,  0.5f, 0.225f, 0.5f };

            float inVals0_1[nSamp] = {-0.000f, -3.0f,  0.00f,    0.0f };
            float inVals1_1[nSamp] = { 0.500f,  1.0f, -1.00f, 1000.0f };
            float outVals1[nSamp]  = { 0.375f,  0.0f, -0.75f,  750.0f };
            
            // Populate rest with random values
            for(uint8_t n = 4; n < nSamp; ++n) {
                float v0 = float(rand()) / float(RAND_MAX);
                float v1 = float(rand()) / float(RAND_MAX);
                float y0 = (v1 - v0) * interpVal + v0;
                float y1 = (v1 - v0) * (1.0f - interpVal) + v0;
                
                inVals0_0[n] = v0;
                inVals1_0[n] = v1;
                outVals0[n]  = y0;
                
                inVals0_1[n] = v1;
                inVals1_1[n] = v0;
                outVals1[n] = y1;
            }
            
            juce::AudioSampleBuffer buf0(2, nSamp);
            juce::AudioSampleBuffer buf1(2, nSamp);
            juce::AudioSampleBuffer outBuf(2, nSamp);
            
            memcpy(buf0.getWritePointer(0), inVals0_0, nSamp*sizeof(float));
            memcpy(buf0.getWritePointer(1), inVals0_1, nSamp*sizeof(float));
            
            memcpy(buf1.getWritePointer(0), inVals1_0, nSamp*sizeof(float));
            memcpy(buf1.getWritePointer(1), inVals1_1, nSamp*sizeof(float));
            
            // Out of place
            Utils::Interp(buf0, buf1, outBuf, interpVal);
            
            float const* rp0 = outBuf.getReadPointer(0);
            float const* rp1 = outBuf.getReadPointer(1);
            for (uint8_t n = 0; n < nSamp; ++n) {
                if (!Utils::ApproxEqual(rp0[n], outVals0[n])) {
                    std::cout << inVals0_0[n] << ", " << inVals1_0 << ", expected " << outVals0[n] << ", got " << rp0[n] << std::endl;
                }
                expect(Utils::ApproxEqual(rp0[n], outVals0[n]));
                
                if (!Utils::ApproxEqual(rp1[n], outVals1[n])) {
                    std::cout << inVals0_1[n] << ", " << inVals1_1 << ", expected " << outVals1[n] << ", got " << rp1[n] << std::endl;
                }
                expect(Utils::ApproxEqual(rp1[n], outVals1[n]));
            }
            
            // In place
            Utils::InterpInPlace(buf0, buf1, interpVal);
            
            rp0 = buf0.getReadPointer(0); rp1 = buf0.getReadPointer(1);
            for (uint8_t n = 0; n < nSamp; ++n) {
                if (!Utils::ApproxEqual(rp0[n], outVals0[n])) {
                    std::cout << inVals0_0[n] << ", " << inVals1_0 << ", expected " << outVals0[n] << ", got " << rp0[n] << std::endl;
                }
                expect(Utils::ApproxEqual(rp0[n], outVals0[n]));
                
                if (!Utils::ApproxEqual(rp1[n], outVals1[n])) {
                    std::cout << inVals0_1[n] << ", " << inVals1_1 << ", expected " << outVals1[n] << ", got " << rp1[n] << std::endl;
                }
                expect(Utils::ApproxEqual(rp1[n], outVals1[n]));
            }
            
            // In-place using out-of-place commands
            
            // reset
            memcpy(buf0.getWritePointer(0), inVals0_0, nSamp*sizeof(float));
            memcpy(buf0.getWritePointer(1), inVals0_1, nSamp*sizeof(float));
            
            Utils::Interp(buf0, buf1, buf0, interpVal);
            
            rp0 = buf0.getReadPointer(0); rp1 = buf0.getReadPointer(1);
            for (uint8_t n = 0; n < nSamp; ++n) {
                if (!Utils::ApproxEqual(rp0[n], outVals0[n])) {
                    std::cout << inVals0_0[n] << ", " << inVals1_0 << ", expected " << outVals0[n] << ", got " << rp0[n] << std::endl;
                }
                expect(Utils::ApproxEqual(rp0[n], outVals0[n]));
                
                if (!Utils::ApproxEqual(rp1[n], outVals1[n])) {
                    std::cout << inVals0_1[n] << ", " << inVals1_1 << ", expected " << outVals1[n] << ", got " << rp1[n] << std::endl;
                }
                expect(Utils::ApproxEqual(rp1[n], outVals1[n]));
            }
            
            // reset
            memcpy(buf0.getWritePointer(0), inVals0_0, nSamp*sizeof(float));
            memcpy(buf0.getWritePointer(1), inVals0_1, nSamp*sizeof(float));
            
            Utils::Interp(buf0, buf1, buf1, interpVal);
            
            rp0 = buf1.getReadPointer(0); rp1 = buf1.getReadPointer(1);
            for (uint8_t n = 0; n < nSamp; ++n) {
                if (!Utils::ApproxEqual(rp0[n], outVals0[n])) {
                    std::cout << inVals0_0[n] << ", " << inVals1_0 << ", expected " << outVals0[n] << ", got " << rp0[n] << std::endl;
                }
                expect(Utils::ApproxEqual(rp0[n], outVals0[n]));
                
                if (!Utils::ApproxEqual(rp1[n], outVals1[n])) {
                    std::cout << inVals0_1[n] << ", " << inVals1_1 << ", expected " << outVals1[n] << ", got " << rp1[n] << std::endl;
                }
                expect(Utils::ApproxEqual(rp1[n], outVals1[n]));
            }
        }
        
        beginTest("Testing GenerateSine");
        {
            uint32_t const nSamp = 16;
            
            AudioSampleBuffer buf(1, nSamp);
            Utils::GenerateSine(buf, 0.125f, -0.25f);
            
            float expVal[nSamp] = {-1.0f, -M_SQRT1_2, 0.0f, M_SQRT1_2, 1.0f, M_SQRT1_2, 0.0f, -M_SQRT1_2,
                                   -1.0f, -M_SQRT1_2, 0.0f, M_SQRT1_2, 1.0f, M_SQRT1_2, 0.0f, -M_SQRT1_2};
            
            float const* rp = buf.getReadPointer(0);
            for (uint32_t n = 0; n < nSamp; ++n) {
                bool bEq = Utils::ApproxEqual(rp[n], expVal[n]);
                if (!bEq)
                    std::cout << "Value " << n << ": expected " << expVal[n] << ", got " << rp[n] << std::endl;
                expect(bEq);
            }
        }

		beginTest("Testing FreqToPhase");
		{
			size_t const nSamp = 5;
			
			float ph = 0.3f;

			float inVals[nSamp] = { 0.35f, 0.1f, 0.4f, 0.01f, 0.2f };
			
			float const expFinal1 = 0.36f;
			
			float const expVals2[nSamp] = { 0.36f, 0.71f, 0.81f, 0.21f, 0.22f };
			float const expFinal2 = 0.42f;
			
			Utils::Buffer buf(inVals, nSamp);
			ph = FreqToPhaseNoProcess(buf, ph);

			expect(Utils::ApproxEqual(ph, expFinal1));

			ph = Utils::FreqToPhase(buf, ph);

			for (size_t n = 0; n < nSamp; ++n)
				expect(Utils::ApproxEqual(buf[n], expVals2[n]));

			expect(Utils::ApproxEqual(ph, expFinal2));
		}

		beginTest("Testing TanhApprox");
		{
			const double range = 10.0;
			const double incr = 0.0125;

			double maxErr = 0.0;

			bool bPass = true;
			for (double x = -range; x < range; x += incr) {

				double yExact = tanh(x);
				double yApprox = Utils::TanhApprox<double, true>(x);
				
				double err = abs(1.0 - yApprox / yExact);

				maxErr = std::max(err, maxErr);

				if (!Utils::ApproxEqual(yApprox, yExact, 0.001)) {
					std::cout << "x: " << x << ", yExact: " << yExact << ", yApprox: " << yApprox << std::endl;
					bPass = false;
					break;
				}
			}
			std::cout << "Max error: " << maxErr << std::endl;
			expect(bPass);
		}

		beginTest("Performance testing TanhApprox");
		{
			size_t const nSamp = 4096;
			size_t const nReps = 1024;

			Utils::Buffer inBuf(nSamp);
			Utils::Buffer outBuf(nSamp);

			float* pIn = inBuf.Get();
			float* pOut = outBuf.Get();

			for (uint32_t n = 0; n < nSamp; ++n) {
				float randVal = float(rand()) / float(RAND_MAX);
				randVal -= 0.5f;
				pIn[n] = randVal * 5.0f;
			}

			double duration;

			
			duration = 0.0;
			for (size_t rep = 0; rep < nReps; ++rep) {
				StartTimer();
				for (size_t n = 0; n < nSamp; ++n) {
					pOut[n] = tanh(pIn[n]);
				}
				duration += StopTimer();
			}
			double const timeActual_s = duration;

			duration = 0.0;
			for (size_t rep = 0; rep < nReps; ++rep) {
				StartTimer();
				for (size_t n = 0; n < nSamp; ++n) {
					pOut[n] = Utils::TanhApprox(pIn[n]);
				}
				duration += StopTimer();
			}
			double const timeApprox_s = duration;

			duration = 0.0;
			for (size_t rep = 0; rep < nReps; ++rep) {
				StartTimer();
				for (size_t n = 0; n < nSamp; ++n) {
					pOut[n] = Utils::TanhApprox<float, false>(pIn[n]);
				}
				duration += StopTimer();
			}
			double const timeApproxNoClip_s = duration;

			duration = 0.0;
			for (size_t rep = 0; rep < nReps; ++rep) {
				StartTimer();
				Utils::TanhApprox(inBuf, outBuf);
				duration += StopTimer();
			}
			double const timeVector_s = duration;

			std::cout << "tanh              total time: " << timeActual_s << " s" << std::endl;
			std::cout << "TanhApprox        total time: " << timeApprox_s << " s" << std::endl;
			std::cout << "TanhApprox noclip total time: " << timeApproxNoClip_s << " s" << std::endl;
			std::cout << "TanhApprox vector total time: " << timeVector_s << " s" << std::endl;

			expect(timeApprox_s < timeActual_s);
			expect(timeApproxNoClip_s < timeActual_s);
			expect(timeVector_s < timeActual_s);
		}
    }

} // namespace Test