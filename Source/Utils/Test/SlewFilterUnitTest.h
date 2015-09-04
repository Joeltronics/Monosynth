/*
  ==============================================================================

    SlewFilterUnitTest.h
    Created: 1 Aug 2015 5:32:21pm
    Author:  Joel Geddert

  ==============================================================================
*/

#ifndef SLEWFILTERUNITTEST_H_INCLUDED
#define SLEWFILTERUNITTEST_H_INCLUDED

#include "JuceHeader.h"

namespace Test {
    
    class SlewFilterUnitTest : public juce::UnitTest {
    public:
        SlewFilterUnitTest();
        void runTest();
    };
    
} // namespace Test


#endif  // SLEWFILTERUNITTEST_H_INCLUDED
