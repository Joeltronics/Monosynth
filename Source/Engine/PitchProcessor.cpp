/*
  ==============================================================================

    PitchProcessor.cpp
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

#include "PitchProcessor.h"

#include "Types.h"

#include <cmath>

namespace Engine {

// Freq for pitch bend smoothing lowpass filter
const double k_pbLowpassFreq = 1000.0;

// Dead zone of pitch bend wheel at center and ends
const uint16_t k_pbStickiness = 0x003F;

PitchProcessor::PitchProcessor() :
	m_sampleRate(0.0),
	m_lastPitchBend(0x2000)
{}

PitchProcessor::~PitchProcessor()
{}

void PitchProcessor::PrepareToPlay(double sampleRate, int /*samplesPerBlock*/) {
	m_sampleRate = sampleRate;
	m_pitchBendFilt.SetFreq(k_pbLowpassFreq / sampleRate);
}

void PitchProcessor::ProcessPitchBend(Buffer& pitchBuf /*inout*/, eventBuf_t<uint16_t> const& pbEvents, uint32_t pbAmt) {
	DEBUG_ASSERT(m_sampleRate > 0.0);

	std::function<float(uint16_t)> mappingFunc =
		[pbAmt](uint16_t pb) -> float
	{
		// First, if near center or end of range, snap
		if (pb <= k_pbStickiness)
			return -float(pbAmt);

		if (pb >= (0x3FFF - k_pbStickiness))
			return float(pbAmt);

		if (pb >= (0x1FFF - k_pbStickiness) &&
			pb <= (0x2000 + k_pbStickiness))
			return 0.0f;

		// Convert [0,0x3FFF] to [0.0f,1.0f]
		float val = float(pb) / float(0x3FFF);
		
		// Convert [0.0f,1.0f] to [-1.0f,1.0f]
		val = (val - 0.5f) * 2.0f;

		val *= float(pbAmt);
		return val;
	};

	Buffer pbBuf(pitchBuf.GetLength());
	
	m_lastPitchBend = Utils::EventBufToBuf<uint16_t, float>(
		m_lastPitchBend, pbEvents, pbBuf.GetLength(), pbBuf.Get(), mappingFunc);

	m_pitchBendFilt.ProcessLowpass(pbBuf);

	pitchBuf += pbBuf;
}

void PitchProcessor::PitchToFreq(Buffer& buf) {
	float* p = buf.Get();
	for (size_t n = 0; n < buf.GetLength(); ++n) {
		p[n] = PitchToNormFreq(p[n]);
	}
}
void PitchProcessor::PitchToFreq(Buffer const& inBuf, Buffer& outBuf) {
	DEBUG_ASSERT(inBuf.GetLength() == outBuf.GetLength());

	float const* pIn = inBuf.GetConst();
	float* pOut = outBuf.Get();

	for (size_t n = 0; n < inBuf.GetLength(); ++n) {
		pOut[n] = PitchToNormFreq(pIn[n]);
	}
}

}