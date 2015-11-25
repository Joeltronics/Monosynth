/*
  ==============================================================================

    OnePoleTest.h
    Created: 16 Aug 2015 12:32:03pm
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
		void RiseTimeTest_();
    };

} // namespace Test

#endif  // ONEPOLETEST_H_INCLUDED
