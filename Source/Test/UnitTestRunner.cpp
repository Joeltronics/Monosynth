/*
  ==============================================================================

    UnitTestRunner.cpp
    Created: 1 Aug 2015 5:37:01pm
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

#include "UnitTestRunner.h"

#include <iostream>
#include "JuceHeader.h"

#include "Utils/Test/DspUtilsUnitTest.h"
#include "Utils/Test/BufferUnitTest.h"
#include "Utils/Test/SlewFilterUnitTest.h"
#include "Utils/Test/ResamplingUnitTest.h"
#include "Utils/Test/OnePoleTest.h"

#include "Engine/Test/EnvelopeUnitTest.h"
#include "Engine/Test/MidiProcessorUnitTest.h"
#include "Engine/Test/PitchProcessorUnitTest.h"

#include "Engine/Test/EngineTest.h"
//#include "Engine/Test/OscillatorTest.h"

namespace Test {
    
    // Utils unit tests
    static DspUtilsUnitTest s_dspUtilsTest;
	static BufferUnitTest s_bufferTest;
    static SlewFilterUnitTest s_slewFilterTest;
    static ResamplingUnitTest s_resampTest;
    
	// Engine unit tests
	static EnvelopeUnitTest s_envTest;
	static MidiProcessorUnitTest s_midiProcTest;
	static PitchProcessorUnitTest s_pitchProcTest;

    // Performance tests
	static EngineTest s_engineTest;
	//static OscillatorTest s_oscTest;
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