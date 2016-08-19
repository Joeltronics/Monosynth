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
	virtual ~Envelope() {}

	virtual void Process(eventBuf_t<gateEvent_t> const& /*in*/, BufferOrVal& /*out*/) = 0;
	virtual void PrepareToPlay(double sampleRate, int samplesPerBlock) = 0;

private:

};

// Basic on/off envelope
class GateEnvelope : public Envelope {
public:
	GateEnvelope();
	~GateEnvelope() {}

	void Process(eventBuf_t<gateEvent_t> const& /*in*/, BufferOrVal& /*out*/) override;
	void PrepareToPlay(double sampleRate, int samplesPerBlock) override;

private:
	Utils::OnePole m_filt;
	gateEvent_t m_lastGate;
};

// Envelope with just attack & decay
class AdEnvelope : public Envelope {
public:
	AdEnvelope();
	~AdEnvelope() {}

	void Process(eventBuf_t<gateEvent_t> const& /*in*/, BufferOrVal& /*out*/) override;
	void PrepareToPlay(double sampleRate, int samplesPerBlock) override;

	void SetVals(double attTime, double decTime, bool bLooped);

private:

	enum State_t {
		state_off = 0,
		state_rise,
		state_fall
	};

	float ProcessSample_();

	double m_sampleRate;

	bool m_bLooped;
	float m_riseRate;
	float m_fallRate;

	float m_z;
	State_t m_state;
};

// Full ADSR envelope
class AdsrEnvelope : public Envelope {
public:
	AdsrEnvelope();

	~AdsrEnvelope() {}

	void Process(eventBuf_t<gateEvent_t> const& /*in*/, BufferOrVal& /*out*/) override;
	void PrepareToPlay(double sampleRate, int samplesPerBlock) override;

	void SetVals(double attTime, double decTime, double susVal, double relVal);

private:

	enum State_t {
		state_off = 0,
		state_att,
		state_dec,
		state_sus,
		state_rel
	};

	sample_t ProcessState_();
	void TransitionTo_(State_t toState);
	sample_t StateAtt_();
	sample_t StateDec_();
	sample_t StateSus_();
	sample_t StateRel_();

	Utils::OnePole m_filt;

	State_t m_state;
	double m_sampleRate;

	double m_attFreq;
	double m_decFreq;
	sample_t m_susVal;
	sample_t m_susTarget;
	double m_relFreq;
};

}

#endif  // ENVELOPE_H_INCLUDED
