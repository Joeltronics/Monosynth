/*
  ==============================================================================

    Debug.h
    Created: 12 Aug 2015 8:44:31am
    Author:  Joel Geddert

  ==============================================================================
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
