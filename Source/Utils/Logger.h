/*
  ==============================================================================

    Logger.h
    Created: 12 Sep 2015 12:25:29am
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
