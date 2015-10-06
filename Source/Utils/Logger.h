/*
  ==============================================================================

    Logger.h
    Created: 12 Sep 2015 12:25:29am
    Author:  Joel

  ==============================================================================
*/

#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include "JuceHeader.h"
#include "Debug.h"

#define STRINGIFY(X) DO_STRINGIFY(X)
#define DO_STRINGIFY(X) #X

namespace Utils {

#if _DEBUG
static void SetupLogger(juce::String const& filename) {
	static juce::File logfile(filename);
	static juce::FileLogger fl(logfile, juce::String("Monosynth starting"), 1000);

	juce::Logger::setCurrentLogger(&fl);
}

#define LOG(MSG) juce::Logger::writeToLog( juce::String::formatted( __FILE__ ":" STRINGIFY(__LINE__) " ") + juce::String(MSG) )

#else

static void SetupLogger(juce::String const& /*filename*/)
{}

#define LOG(MSG)

#endif


} // namespace Utils

#endif  // LOGGER_H_INCLUDED
