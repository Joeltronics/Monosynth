/*
  ==============================================================================

    SlewFilterUnitTest.cpp
    Created: 1 Aug 2015 5:45:22pm
    Author:  Joel Geddert

  ==============================================================================
*/

#include "SlewFilterUnitTest.h"

#include "JuceHeader.h"

#include "Utils/DspUtils.h"

#include <vector>

namespace Test {

    SlewFilterUnitTest::SlewFilterUnitTest()
        : UnitTest("SlewFilter unit test")
    {}
    
    void SlewFilterUnitTest::runTest()
    {
        beginTest("Testing SlewFilter, one sample at a time");
        {
            Utils::SlewFilter filter(1, 0.25f);
            
            float samp;
            std::vector<float> inVals;
            std::vector<float> outVals;
            
            inVals  = { 1.00f, 1.00f, 1.00f, 1.00f, 1.00f };
            outVals = { 0.25f, 0.50f, 0.75f, 1.00f, 1.00f };
            
            for (size_t n = 0; n < inVals.size(); ++n) {
                samp = filter.Process(inVals[n], 0);
                if (!Utils::ApproxEqual(samp, outVals[n]))
                    std::cout << "Input: " << inVals[n] << ", expect: " << outVals[n] << ", actual: " << samp << std::endl;
                expect(Utils::ApproxEqual(samp, outVals[n]));
            }
            
            filter.Clear();
            filter.SetRate(0.3f);
            
            inVals  = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
            outVals = { 0.3f, 0.6f, 0.9f, 1.0f, 1.0f };

            for (size_t n = 0; n < inVals.size(); ++n) {
                samp = filter.Process(inVals[n], 0);
                if (!Utils::ApproxEqual(samp, outVals[n]))
                    std::cout << "Input: " << inVals[n] << ", expect: " << outVals[n] << ", actual: " << samp << std::endl;
                expect(Utils::ApproxEqual(samp, outVals[n]));
            }
            
            filter.Clear();
            
            inVals  = { -1.0f, -1.0f,  0.0f, 1.0f, 0.5f, 0.5f };
            outVals = { -0.3f, -0.6f, -0.3f, 0.0f, 0.3f, 0.5f };
            
            for (size_t n = 0; n < inVals.size(); ++n) {
                samp = filter.Process(inVals[n], 0);
                if (!Utils::ApproxEqual(samp, outVals[n]))
                    std::cout << "Input: " << inVals[n] << ", expect: " << outVals[n] << ", actual: " << samp << std::endl;
                expect(Utils::ApproxEqual(samp, outVals[n]));
            }
        }
        
        beginTest("Testing SlewFilter with changing rate");
        {
            Utils::SlewFilter filter(1, 0.25f);
            
            float samp;
            std::vector<float> inVals;
            std::vector<float> rate;
            std::vector<float> outVals;
            
            inVals  = { 1.00f, 1.00f, 2.00f, -1.00f, -1.00f };
            rate    = { 0.25f, 0.50f, 0.30f,  2.00f,  2.00f };
            outVals = { 0.25f, 0.75f, 1.05f, -0.95f, -1.00f };
            
            for (size_t n = 0; n < inVals.size(); ++n) {
                filter.SetRate(rate[n]);
                samp = filter.Process(inVals[n], 0);
                if (!Utils::ApproxEqual(samp, outVals[n]))
                    std::cout << "Input: "<< inVals[n] <<", rate: "<< rate[n] <<", expect: "<< outVals[n] <<", actual: "<< samp << std::endl;
                expect(Utils::ApproxEqual(samp, outVals[n]));
            }
        }
         
        beginTest("Testing SlewFilter on raw float* buffers");
        {
            Utils::SlewFilter filter(2, 0.3f);
            
            float inVals[6] = { -1.0f, -1.0f,  0.0f, 1.0f, 0.5f, 0.5f };
            float expVals[6] = { -0.3f, -0.6f, -0.3f, 0.0f, 0.3f, 0.5f };
            
            float outVals[6];
            float inPlaceVals[6];
            memcpy(inPlaceVals, inVals, 6*sizeof(float));
            
            filter.Process(inVals, outVals, 6, 0);
            filter.Process(inPlaceVals, 6, 1);
            
            for (size_t n = 0; n < 6; ++n) {
                if (!Utils::ApproxEqual(outVals[n], expVals[n]))
                    std::cout << "Out-of-place: In: " << inVals[n] << ", expect: " << expVals[n] << ", actual: " << outVals[n] << std::endl;
                expect(Utils::ApproxEqual(outVals[n], expVals[n]));
                
                if (!Utils::ApproxEqual(inPlaceVals[n], expVals[n]))
                    std::cout << "In-Place:     In: " << inVals[n] << ", expect: " << expVals[n] << ", actual: " << inPlaceVals[n] << std::endl;
                expect(Utils::ApproxEqual(inPlaceVals[n], expVals[n]));
            }
        }
        
        beginTest("Testing SlewFilter on AudioSampleBuffer");
        {
            juce::AudioSampleBuffer buf(3, 8);
            
            Utils::SlewFilter filter(3, 0.3f);
            
            float inVals0[8]  = { -1.0f, -1.0f,  0.0f, 1.0f, 0.5f, 0.5f, 0.0f, 0.0f };
            float expVals0[8] = { -0.3f, -0.6f, -0.3f, 0.0f, 0.3f, 0.5f, 0.2f, 0.0f };
            
            float inVals1[8]  = { -1.0f, 1.0f, 0.1f, -0.1f, 0.5f, 0.5f, 1.0f, 1.0f };
            float expVals1[8] = { -0.3f, 0.0f, 0.1f, -0.1f, 0.2f, 0.5f, 0.8f, 1.0f };
            
            float inVals2[8]  = { -1.0f, 1.0f, 0.1f, -0.1f, 0.5f, 0.5f, 1.0f, 1.0f };
            float expVals2[8] = { -0.3f, 0.0f, 0.1f, -0.1f, 0.2f, 0.5f, 0.8f, 1.0f };
            
            memcpy(buf.getWritePointer(0), inVals0, 8*sizeof(float));
            memcpy(buf.getWritePointer(1), inVals1, 8*sizeof(float));
            memcpy(buf.getWritePointer(2), inVals2, 8*sizeof(float));
            
            juce::AudioSampleBuffer inBuf = buf;
            juce::AudioSampleBuffer outBuf(3, 8);

            filter.Process(inBuf, outBuf);
            filter.Clear();
            filter.Process(inBuf);

            float const* ip0 = inBuf.getReadPointer(0);
            float const* ip1 = inBuf.getReadPointer(1);
            float const* ip2 = inBuf.getReadPointer(1);
            
            float const* op0 = outBuf.getReadPointer(0);
            float const* op1 = outBuf.getReadPointer(1);
            float const* op2 = outBuf.getReadPointer(2);
            
            for (size_t n = 0; n < 8; ++n) {
                
                if (!Utils::ApproxEqual(op0[n], expVals0[n]))
                    std::cout << "Out-of-place 0: In: " << inVals0[n] << ", expect: " << expVals0[n] << ", actual: " << op0[n] << std::endl;
                expect(Utils::ApproxEqual(op0[n], expVals0[n]));
                
                if (!Utils::ApproxEqual(op1[n], expVals1[n]))
                    std::cout << "Out-of-place 1: In: " << inVals1[n] << ", expect: " << expVals1[n] << ", actual: " << op1[n] << std::endl;
                expect(Utils::ApproxEqual(op1[n], expVals1[n]));
                
                if (!Utils::ApproxEqual(op2[n], expVals2[n]))
                    std::cout << "Out-of-place 2: In: " << inVals2[n] << ", expect: " << expVals2[n] << ", actual: " << op2[n] << std::endl;
                expect(Utils::ApproxEqual(op2[n], expVals2[n]));
                
                if (!Utils::ApproxEqual(ip0[n], expVals0[n]))
                    std::cout << "In-Place 0:     In: " << inVals0[n] << ", expect: " << expVals0[n] << ", actual: " << ip0[n] << std::endl;
                expect(Utils::ApproxEqual(ip0[n], expVals0[n]));
                
                if (!Utils::ApproxEqual(ip1[n], expVals1[n]))
                    std::cout << "In-Place 1:     In: " << inVals1[n] << ", expect: " << expVals1[n] << ", actual: " << ip1[n] << std::endl;
                expect(Utils::ApproxEqual(ip1[n], expVals1[n]));
                
                if (!Utils::ApproxEqual(ip2[n], expVals2[n]))
                    std::cout << "In-Place 2:     In: " << inVals2[n] << ", expect: " << expVals2[n] << ", actual: " << ip2[n] << std::endl;
                expect(Utils::ApproxEqual(ip2[n], expVals2[n]));
            }
        }
    }

} // namespace Test