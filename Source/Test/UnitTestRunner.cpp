/*
  ==============================================================================

    UnitTestRunner.cpp
    Created: 1 Aug 2015 5:37:01pm
    Author:  Joel Geddert

  ==============================================================================
*/

#include "UnitTestRunner.h"

#include <iostream>
#include "JuceHeader.h"

#include "Utils/Test/DspUtilsUnitTest.h"
#include "Utils/Test/SlewFilterUnitTest.h"
#include "Utils/Test/ResamplingUnitTest.h"
#include "Utils/Test/OnePoleTest.h"

#include "Engine/Test/EnvelopeUnitTest.h"
#include "Engine/Test/MidiProcessorUnitTest.h"

namespace Test {
    
    // Utils unit tests
    static DspUtilsUnitTest s_dspUtilsTest;
    static SlewFilterUnitTest s_slewFilterTest;
    static ResamplingUnitTest s_resampTest;
    
	// Engine unit tests
	static EnvelopeUnitTest s_envTest;
	static MidiProcessorUnitTest s_midiProcTest;

    // Performance tests
    static OnePoleTest s_onePoleTest;
    
    void RunAllUnitTests() {
        std::cout << "\nRunAllUnitTests() called\n\n";
        
        /*
         std::cout << "\nTrying vanilla JUCE UnitTestRunner\n";
         {
         UnitTestRunner runner;
         runner.runAllTests();
         }
         //*/
        
        std::cout << "\nTrying FreeSynthUnitTestRunner\n";
        {
            OverdrivePedalUnitTestRunner runner;
            runner.setAssertOnFailure(false);
            runner.runAllTests();
        }
        
        std::cout << "\nRunAllUnitTests() Done!\n\n";
    }
    
    OverdrivePedalUnitTestRunner::OverdrivePedalUnitTestRunner()
    {}
    
    OverdrivePedalUnitTestRunner::~OverdrivePedalUnitTestRunner()
    {}
    
    int OverdrivePedalUnitTestRunner::run()
    {
        runAllTests();
        return 0;
    }
    
    void OverdrivePedalUnitTestRunner::logMessage(juce::String const& message) {
        
        std::cout << message << "\n";
        
    }
    
} // namespace Test