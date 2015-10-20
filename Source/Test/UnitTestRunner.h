/*
  ==============================================================================

    UnitTestRunner.h
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
