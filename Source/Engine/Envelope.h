/*
  ==============================================================================

    Envelope.h
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

#ifndef ENVELOPE_H_INCLUDED
#define ENVELOPE_H_INCLUDED

#include "Types.h"
#include "Utils/OnePole.h"

namespace Engine {

class Envelope {
public:
	Envelope() {}
	~Envelope() {}

	virtual void Process(eventBuf_t<gateEvent_t> /*in*/, Buffer& /*out*/) = 0;
	virtual void PrepareToPlay(double sampleRate, int samplesPerBlock) = 0;

private:

};

class GateEnvelope : public Envelope {
public:
	GateEnvelope();
	~GateEnvelope() {}

	void Process(eventBuf_t<gateEvent_t> /*in*/, Buffer& /*out*/) override;
	void PrepareToPlay(double sampleRate, int samplesPerBlock) override;

private:
	Utils::OnePole m_filt;
	gateEvent_t m_lastGate;
};

class AdsrEnvelope : public Envelope {
public:
	AdsrEnvelope();
	~AdsrEnvelope() {}

	void Process(eventBuf_t<gateEvent_t> /*in*/, Buffer& /*out*/) override;
	void PrepareToPlay(double sampleRate, int samplesPerBlock) override;

private:
	sample_t m_memory;
};

}

#endif  // ENVELOPE_H_INCLUDED
