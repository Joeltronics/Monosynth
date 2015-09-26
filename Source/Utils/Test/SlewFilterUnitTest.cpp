/*
  ==============================================================================

    SlewFilterUnitTest.cpp
    Created: 1 Aug 2015 5:45:22pm
    Author:  Joel Geddert

  ==============================================================================
*/

#include "SlewFilterUnitTest.h"

#include "JuceHeader.h"

#include "Utils/Utils.h"

#include <vector>

using namespace Utils;

namespace Test {

    SlewFilterUnitTest::SlewFilterUnitTest()
        : UnitTest("SlewFilter unit test")
    {}
    
    void SlewFilterUnitTest::runTest()
    {
        beginTest("Testing SlewFilter, one sample at a time");
        {
            Utils::SlewFilter filter(0.25f);
            
            float samp;
            std::vector<float> inVals;
            std::vector<float> outVals;
            
            inVals  = { 1.00f, 1.00f, 1.00f, 1.00f, 1.00f };
            outVals = { 0.25f, 0.50f, 0.75f, 1.00f, 1.00f };
            
            for (size_t n = 0; n < inVals.size(); ++n) {
                samp = filter.Process(inVals[n]);
                if (!Utils::ApproxEqual(samp, outVals[n]))
                    std::cout << "Input: " << inVals[n] << ", expect: " << outVals[n] << ", actual: " << samp << std::endl;
                expect(Utils::ApproxEqual(samp, outVals[n]));
            }
            
            filter.Clear();
            filter.SetRate(0.3f);
            
            inVals  = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
            outVals = { 0.3f, 0.6f, 0.9f, 1.0f, 1.0f };

            for (size_t n = 0; n < inVals.size(); ++n) {
                samp = filter.Process(inVals[n]);
                if (!Utils::ApproxEqual(samp, outVals[n]))
                    std::cout << "Input: " << inVals[n] << ", expect: " << outVals[n] << ", actual: " << samp << std::endl;
                expect(Utils::ApproxEqual(samp, outVals[n]));
            }
            
            filter.Clear();
            
            inVals  = { -1.0f, -1.0f,  0.0f, 1.0f, 0.5f, 0.5f };
            outVals = { -0.3f, -0.6f, -0.3f, 0.0f, 0.3f, 0.5f };
            
            for (size_t n = 0; n < inVals.size(); ++n) {
                samp = filter.Process(inVals[n]);
                if (!Utils::ApproxEqual(samp, outVals[n]))
                    std::cout << "Input: " << inVals[n] << ", expect: " << outVals[n] << ", actual: " << samp << std::endl;
                expect(Utils::ApproxEqual(samp, outVals[n]));
            }
        }
        
        beginTest("Testing SlewFilter with changing rate");
        {
            Utils::SlewFilter filter(0.25f);
            
            float samp;
            std::vector<float> inVals;
            std::vector<float> rate;
            std::vector<float> outVals;
            
            inVals  = { 1.00f, 1.00f, 2.00f, -1.00f, -1.00f };
            rate    = { 0.25f, 0.50f, 0.30f,  2.00f,  2.00f };
            outVals = { 0.25f, 0.75f, 1.05f, -0.95f, -1.00f };
            
            for (size_t n = 0; n < inVals.size(); ++n) {
                filter.SetRate(rate[n]);
                samp = filter.Process(inVals[n]);
                if (!Utils::ApproxEqual(samp, outVals[n]))
                    std::cout << "Input: "<< inVals[n] <<", rate: "<< rate[n] <<", expect: "<< outVals[n] <<", actual: "<< samp << std::endl;
                expect(Utils::ApproxEqual(samp, outVals[n]));
            }
        }
         
        beginTest("Testing SlewFilter on raw float* buffers");
        {
            Utils::SlewFilter filter(0.3f);
            
            float inVals[6] = { -1.0f, -1.0f,  0.0f, 1.0f, 0.5f, 0.5f };
            float expVals[6] = { -0.3f, -0.6f, -0.3f, 0.0f, 0.3f, 0.5f };
            
            float outVals[6];
            float inPlaceVals[6];
            memcpy(inPlaceVals, inVals, 6*sizeof(float));
            
            filter.Process(inVals, outVals, 6);
			filter.Clear();
            filter.Process(inPlaceVals, 6);
            
            for (size_t n = 0; n < 6; ++n) {
                if (!Utils::ApproxEqual(outVals[n], expVals[n]))
                    std::cout << "Out-of-place: In: " << inVals[n] << ", expect: " << expVals[n] << ", actual: " << outVals[n] << std::endl;
                expect(Utils::ApproxEqual(outVals[n], expVals[n]));
                
                if (!Utils::ApproxEqual(inPlaceVals[n], expVals[n]))
                    std::cout << "In-Place:     In: " << inVals[n] << ", expect: " << expVals[n] << ", actual: " << inPlaceVals[n] << std::endl;
                expect(Utils::ApproxEqual(inPlaceVals[n], expVals[n]));
            }
        }
        
        beginTest("Testing SlewFilter on Buffer");
        {
            Utils::SlewFilter filter(0.3f);
            
            float inVals0[8]  = { -1.0f, -1.0f,  0.0f, 1.0f, 0.5f, 0.5f, 0.0f, 0.0f };
            float expVals0[8] = { -0.3f, -0.6f, -0.3f, 0.0f, 0.3f, 0.5f, 0.2f, 0.0f };
            
            float inVals1[8]  = { -1.0f, 1.0f, 0.1f, -0.1f, 0.5f, 0.5f, 1.0f, 1.0f };
            float expVals1[8] = { -0.3f, 0.0f, 0.1f, -0.1f, 0.2f, 0.5f, 0.8f, 1.0f };
            
            float inVals2[8]  = { -1.0f, 1.0f, 0.1f, -0.1f, 0.5f, 0.5f, 1.0f, 1.0f };
            float expVals2[8] = { -0.3f, 0.0f, 0.1f, -0.1f, 0.2f, 0.5f, 0.8f, 1.0f };
            
			Buffer buf0(inVals0, 8);
			Buffer buf1(inVals1, 8);
			Buffer buf2(inVals2, 8);

			Buffer outBuf0(8);
			Buffer outBuf1(8);
			Buffer outBuf2(8);

            filter.Process(buf0, outBuf0);
            filter.Clear();
			filter.Process(buf1, outBuf1);
			filter.Clear();
			filter.Process(buf2, outBuf2);
			filter.Clear();
			filter.Process(buf0);
			filter.Clear();
			filter.Process(buf1);
			filter.Clear();
			filter.Process(buf2);

            for (size_t n = 0; n < 8; ++n) {
                
                if (!Utils::ApproxEqual(outBuf0[n], expVals0[n]))
                    std::cout << "Out-of-place 0: In: " << inVals0[n] << ", expect: " << expVals0[n] << ", actual: " << outBuf0[n] << std::endl;
                expect(Utils::ApproxEqual(outBuf0[n], expVals0[n]));
                
                if (!Utils::ApproxEqual(outBuf1[n], expVals1[n]))
                    std::cout << "Out-of-place 1: In: " << inVals1[n] << ", expect: " << expVals1[n] << ", actual: " << outBuf1[n] << std::endl;
                expect(Utils::ApproxEqual(outBuf1[n], expVals1[n]));
                
                if (!Utils::ApproxEqual(outBuf2[n], expVals2[n]))
                    std::cout << "Out-of-place 2: In: " << inVals2[n] << ", expect: " << expVals2[n] << ", actual: " << outBuf2[n] << std::endl;
                expect(Utils::ApproxEqual(outBuf2[n], expVals2[n]));
                
                if (!Utils::ApproxEqual(buf0[n], expVals0[n]))
                    std::cout << "In-Place 0:     In: " << inVals0[n] << ", expect: " << expVals0[n] << ", actual: " << buf0[n] << std::endl;
                expect(Utils::ApproxEqual(buf0[n], expVals0[n]));
                
                if (!Utils::ApproxEqual(buf1[n], expVals1[n]))
                    std::cout << "In-Place 1:     In: " << inVals1[n] << ", expect: " << expVals1[n] << ", actual: " << buf1[n] << std::endl;
                expect(Utils::ApproxEqual(buf1[n], expVals1[n]));
                
                if (!Utils::ApproxEqual(buf2[n], expVals2[n]))
                    std::cout << "In-Place 2:     In: " << inVals2[n] << ", expect: " << expVals2[n] << ", actual: " << buf2[n] << std::endl;
                expect(Utils::ApproxEqual(buf2[n], expVals2[n]));
            }
        }
    }

} // namespace Test