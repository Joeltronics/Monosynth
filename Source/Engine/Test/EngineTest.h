/*
  ==============================================================================

    EngineTest.h
    Created: 5 Oct 2015 7:36:27pm
    Author:  Joel

  ==============================================================================
*/

#ifndef ENGINETEST_H_INCLUDED
#define ENGINETEST_H_INCLUDED

#include "JuceHeader.h"

namespace Test {

	class EngineTest : public juce::UnitTest {
	public:
		EngineTest();
		void runTest();
	};

}



#endif  // ENGINETEST_H_INCLUDED
