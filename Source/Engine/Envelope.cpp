/*
  ==============================================================================

    Envelope.cpp
    Created: 28 Sep 2015 9:16:52pm
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

#include "Envelope.h"
#include "Utils/Debug.h"

namespace Engine {

static const double k_gateLowpassFreq = 2000.0;

GateEnvelope::GateEnvelope() :
	m_lastGate(gateEvent_off)
{}

void GateEnvelope::Process(eventBuf_t<gateEvent_t> gateEvents /*in*/, Buffer& buf /*out*/) {

	// FIXME: This will give an instant transition, could "pop"
	// Simple solution is to lowpass filter, but there are much more efficient solutions

	std::function<sample_t(gateEvent_t)> mappingFunc =
		[](gateEvent_t ev) -> sample_t
		{
			return (ev == gateEvent_off ? 0.0f : 1.0f);
		};

	m_lastGate = Utils::EventBufToBuf<gateEvent_t, sample_t>(
			m_lastGate, gateEvents, buf.GetLength(), buf.Get(), mappingFunc);

	m_filt.ProcessLowpass(buf);
}

void GateEnvelope::PrepareToPlay(double sampleRate, int /*samplesPerBlock*/) {
	m_filt.SetFreq(k_gateLowpassFreq / sampleRate);
}

AdsrEnvelope::AdsrEnvelope() :
	m_memory(0.0f)
{}

void AdsrEnvelope::Process(eventBuf_t<gateEvent_t> gateEvents /*in*/, Buffer& buf /*out*/) {
	DEBUG_ASSERT(false); // TODO
}

void AdsrEnvelope::PrepareToPlay(double /*sampleRate*/, int /*samplesPerBlock*/) {
	// TODO
}

}


