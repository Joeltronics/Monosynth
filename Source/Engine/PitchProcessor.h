/*
  ==============================================================================

    PitchProcessor.h
    Created: 15 Sep 2015 8:13:01am
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

#ifndef PITCHPROCESSOR_H_INCLUDED
#define PITCHPROCESSOR_H_INCLUDED

#include "Types.h"

#include <cmath>

#include "Utils/DspUtils.h"
#include "Utils/Debug.h"
#include "Utils/OnePole.h"

namespace Engine {

class PitchProcessor {
public:

	PitchProcessor();
	~PitchProcessor();

	void PrepareToPlay(double sampleRate, int samplesPerBlock);

	inline float PitchToNormFreq(float pitch) {
		DEBUG_ASSERT(m_sampleRate > 0.0);
		return float(Utils::PitchToFreqHz<double>(pitch) / m_sampleRate);
	}
	
	void PitchToFreq(Buffer& buf);
	void PitchToFreq(Buffer const& inBuf, Buffer& outBuf);

	void ProcessPitchBend(Buffer& pitchBuf /*inout*/, eventBuf_t<uint16_t> const& pitchBendEvents, uint32_t pitchBendAmt);

private:

	double m_sampleRate;
	uint16_t m_lastPitchBend;
	Utils::OnePole m_pitchBendFilt;
	Buffer m_pitchBendBuf;
};

}



#endif  // PITCHPROCESSOR_H_INCLUDED
