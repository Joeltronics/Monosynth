/*
  ==============================================================================

    SlewFilterUnitTest.h
    Created: 1 Aug 2015 5:32:21pm
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
