/*
  ==============================================================================

    ApproxEqual.h
    Created: 5 Aug 2015 8:17:26am
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

#ifndef APPROXEQUAL_H_INCLUDED
#define APPROXEQUAL_H_INCLUDED

#include "Utils/Types.h"
#include "JuceHeader.h"

namespace Utils {

static inline bool ApproxEqual(float a, float b, float thresh = k_defaultApproxEqualThresh) {
    return (std::fabs(a - b) <= thresh);
}

static inline bool ApproxEqual(double a, double b, double thresh = k_defaultApproxEqualThresh) {
	return (std::fabs(a - b) <= thresh);
}

static inline bool ApproxEqual(sample_t const* a, sample_t const* b, uint32_t nValues, sample_t thresh = k_defaultApproxEqualThresh) {
	// TODO: test and see which is faster
#if 1
    sample_t* p = Buffer(nValues).Get();
    juce::FloatVectorOperations::subtract(p, a, b, nValues);
    juce::FloatVectorOperations::abs(p, p, nValues);
    float max = juce::FloatVectorOperations::findMaximum(p, nValues);
    return (max <= thresh);
#else
    bool bEq = true;
    for (uint32_t n = 0; n < nValues; ++n) {
        bEq = bEq && ApproxEqual(a[n], b[n], thresh);
    }
    return bEq;
#endif
}

static inline bool ApproxEqual(Buffer const& a, Buffer const& b, float thresh = k_defaultApproxEqualThresh) {
	if (a.GetLength() != b.GetLength()) return false;
	return ApproxEqual(a.GetConst(), b.GetConst(), a.GetLength(), thresh);
}

static inline bool ApproxEqual(juce::AudioSampleBuffer const& a, juce::AudioSampleBuffer const& b, float thresh = k_defaultApproxEqualThresh) {
    if (a.getNumChannels() != b.getNumChannels() || a.getNumSamples() != b.getNumSamples())
        return false;
    size_t const nChan = a.getNumChannels();
    size_t const nSamp = a.getNumSamples();
    bool bEq = true;
    for (uint8_t chan = 0; chan < nChan; ++chan) {
        bEq = bEq && ApproxEqual(a.getReadPointer(chan), b.getReadPointer(chan), nSamp, thresh);
    }
    return bEq;
}

} // namespace Utils



#endif  // APPROXEQUAL_H_INCLUDED
