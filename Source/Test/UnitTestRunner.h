/*
  ==============================================================================

    UnitTestRunner.h
    Created: 1 Aug 2015 5:37:01pm
    Author:  Joel Geddert

  ==============================================================================
*/

#ifndef UNITTESTRUNNER_H_INCLUDED
#define UNITTESTRUNNER_H_INCLUDED

#include "JuceHeader.h"

namespace Test {
    
    void RunAllUnitTests();
    
    class OverdrivePedalUnitTestRunner : public juce::UnitTestRunner {
        
    public:
        OverdrivePedalUnitTestRunner();
        ~OverdrivePedalUnitTestRunner();
        
        int run();
        
    protected:
        void logMessage(juce::String const& message);
        
    private:
        
    };
}

#endif  // UNITTESTRUNNER_H_INCLUDED
