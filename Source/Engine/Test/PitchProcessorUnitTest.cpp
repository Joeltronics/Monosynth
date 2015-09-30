/*
  ==============================================================================

    PitchProcessorUnitTest.cpp
    Created: 17 Sep 2015 8:52:07am
    Author:  Joel

  ==============================================================================
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