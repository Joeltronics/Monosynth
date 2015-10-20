/*
  ==============================================================================

    PitchProcessorUnitTest.cpp
    Created: 17 Sep 2015 8:52:07am
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

#include "PitchProcessorUnitTest.h"

#include "Engine/PitchProcessor.h"

#include "Utils/ApproxEqual.h"

namespace Test {

PitchProcessorUnitTest::PitchProcessorUnitTest()
	: UnitTest("PitchProcessor unit test")
{}

void PitchProcessorUnitTest::runTest() {
	
	beginTest("PitchProcessor Unit Test");
	{
		Engine::PitchProcessor pitchProc;

		size_t nSamp = 32;
		float sampleRate = 44100.0f;

		pitchProc.PrepareToPlay(sampleRate, nSamp);

		float w;
		w = pitchProc.PitchToNormFreq(69.0f);
		expect(Utils::ApproxEqual(w, 440.0f/sampleRate));

		w = pitchProc.PitchToNormFreq(60.0f);
		expect(Utils::ApproxEqual(w, 261.63f / sampleRate, 0.001f));

		// TODO: test buffered versions
		//void PitchToFreq(Buffer& buf);
		//void PitchToFreq(Buffer const& inBuf, Buffer& outBuf);
	}
}



}