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

using namespace Utils;

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
    juce::ScopedPointer<Utils::IResampler> pResamp;
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
}

} // namespace Test