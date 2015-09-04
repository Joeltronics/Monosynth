/*
  ==============================================================================

    OnePoleTest.h
    Created: 16 Aug 2015 12:32:03pm
    Author:  Joel Geddert

  ==============================================================================
*/

#ifndef ONEPOLETEST_H_INCLUDED
#define ONEPOLETEST_H_INCLUDED

#include "Utils/OnePole.h"

namespace Test {

    class OnePoleTest : public juce::UnitTest {
    public:
        OnePoleTest();
        void runTest();
        
    private:
        void BasicTest_(std::string filename);
        void FreqSweepTest_(std::string filename);
    };

} // namespace Test

#endif  // ONEPOLETEST_H_INCLUDED
