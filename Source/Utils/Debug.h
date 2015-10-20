/*
  ==============================================================================

    Debug.h
    Created: 12 Aug 2015 8:44:31am
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

#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

// (0,0) is to prevent compiler warning "conditional expression is constant"
#define REQUIRE_SEMICOLON(X) \
do { \
    X;\
} while(0,0)

#if _DEBUG


#define IF_DEBUG(X) REQUIRE_SEMICOLON(X)

#else

#define IF_DEBUG(X)

#endif




#if _DEBUG
typedef bool DEBUG_BOOL;
#else
typedef bool const DEBUG_BOOL;
#endif

/*
 TODOs:
 
 Use juce::NativeMessageBox::showMessageBoxAsync
 the problem is this is non-blocking, so leak detector gives error!
 Might have to use juce AlertWindow instead
 
 Use __func__ and __LINE__ macros
 the problem is these give compiler error of missing closing bracket, for some
 strange reason
 */

#if _DEBUG

#include "JuceHeader.h"

#if _CLI // Debug, CLI

#define DEBUG_ASSERT(X) jassert(X)

#else // Debug, GUI

#include "JuceHeader.h"

#define DEBUG_ASSERT(X) REQUIRE_SEMICOLON( \
    if (!(X)) {\
        juce::NativeMessageBox::showOkCancelBox( \
                juce::AlertWindow::WarningIcon, \
                juce::String("Assert Failed"), \
                juce::String( __FILE__ "\n" #X ) \
                ); \
    }\
    jassert(X);\
)

#endif

#else // Release

#define DEBUG_ASSERT(X)

#endif


#endif  // DEBUG_H_INCLUDED
