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
#include "Utils/DspUtils.h"

using namespace Engine;

static const double k_gateLowpassFreq = 2000.0;

// Target for exponential (which triggers at 1.0), ~= 1.582
static const double k_expOvershoot = 1.0 / (1.0 - exp(-1.0));
static const float k_expOvershootf = float(1.0 / (1.0 - exp(-1.0)));

// ********** GateEnvelope ***********

GateEnvelope::GateEnvelope() :
	m_lastGate(gateEvent_off)
{}

void GateEnvelope::PrepareToPlay(double sampleRate, int /*samplesPerBlock*/) {
	m_filt.SetFreq(k_gateLowpassFreq / sampleRate);
}

void GateEnvelope::Process(eventBuf_t<gateEvent_t> gateEvents /*in*/, Buffer& buf /*out*/) {

	// TODO: more efficient solution than just lowpass filter to prevent "pops"

	std::function<sample_t(gateEvent_t)> mappingFunc =
		[](gateEvent_t ev) -> sample_t
		{
			return (ev == gateEvent_off ? 0.0f : 1.0f);
		};

	m_lastGate = Utils::EventBufToBuf<gateEvent_t, sample_t>(
			m_lastGate, gateEvents, buf.GetLength(), buf.Get(), mappingFunc);

	m_filt.ProcessLowpass(buf);
}

// ********** AdEnvelope ***********

AdEnvelope::AdEnvelope() :
	m_sampleRate(0.0)
{}

void AdEnvelope::PrepareToPlay(double sampleRate, int /*samplesPerBlock*/) {
	m_sampleRate = sampleRate;
}

void AdEnvelope::SetVals(double attTime, double decTime, bool bLooped) {
	// TODO
	m_bLooped = bLooped;
}

void AdEnvelope::Process(eventBuf_t<gateEvent_t> gateEvents /*in*/, Buffer& buf /*out*/) {
	// TODO
	buf.Set(1.0f);
}

// ********** AdsrEnvelope ***********

AdsrEnvelope::AdsrEnvelope() :
	m_state(state_off),
	m_sampleRate(0.0)
{
	DEBUG_ASSERT(abs(k_expOvershoot - 1.582) < 0.01);
}

void AdsrEnvelope::Process(eventBuf_t<gateEvent_t> gateEvents /*in*/, Buffer& buf /*out*/) {
	DEBUG_ASSERT(m_sampleRate > 0.0);
	
	eventBuf_t<gateEvent_t>::const_iterator it = gateEvents.begin();

	size_t nextEvent = (it != gateEvents.end()) ? it->time : size_t(-1);

	float* bp = buf.Get();
	for (size_t n = 0; n < buf.GetLength(); ++n) {

		// while loop is in case multiple events at same timestamp
		while (n == nextEvent) {
			switch (it->ev) {
			case gateEvent_on_trig:
			case gateEvent_retrig:
				m_filt.Clear();
				TransitionTo_(state_att);
				break;
			case gateEvent_on_legato:
				TransitionTo_(state_att);
				break;
			case gateEvent_off:
				TransitionTo_(state_rel);
				break;
			case gateEvent_legato:
			default:
				break;
			}

			++it;
			nextEvent = (it != gateEvents.end()) ? it->time : size_t(-1);
		}

		bp[n] = ProcessState_();
	}
}

void AdsrEnvelope::PrepareToPlay(double sampleRate, int /*samplesPerBlock*/) {
	m_sampleRate = sampleRate;
}

void AdsrEnvelope::SetVals(double attTime, double decTime, double susVal, double relTime) {

	// Clip to range 0.01 ms to 100 s
	attTime = Utils::Clip(attTime, 0.01/1000.0, 100.0);
	decTime = Utils::Clip(decTime, 0.01/1000.0, 100.0);
	relTime = Utils::Clip(relTime, 0.01/1000.0, 100.0);

	susVal = Utils::Clip(susVal, 0.0, 1.0);

	//double wc = 1.0 / (2.0 * M_PI * riseTime_s * sampleRate);

	m_attFreq = 1.0 / (2.0 * M_PI * attTime * m_sampleRate);
	m_decFreq = 1.0 / (2.0 * M_PI * decTime * m_sampleRate);
	m_relFreq = 1.0 / (2.0 * M_PI * relTime * m_sampleRate);

	m_susVal = float(susVal);
	m_susTarget = float(1.0 - (k_expOvershoot * (1.0 - susVal)));

	// sanity checks
	DEBUG_ASSERT(m_attFreq > 0.0);
	DEBUG_ASSERT(m_decFreq > 0.0);
	DEBUG_ASSERT(m_relFreq > 0.0);

	DEBUG_ASSERT(m_attFreq < 0.25);
	DEBUG_ASSERT(m_decFreq < 0.25);
	DEBUG_ASSERT(m_relFreq < 0.25);

	DEBUG_ASSERT(m_susTarget < (susVal + 0.01));
	DEBUG_ASSERT(m_susTarget > (1.0 - k_expOvershoot - 0.01));
}

sample_t AdsrEnvelope::ProcessState_() {
	switch (m_state) {
	case state_att: return StateAtt_();
	case state_dec: return StateDec_();
	case state_sus: return StateSus_();
	case state_rel: return StateRel_();
	case state_off:
	default:
		return 0.0f;
	}
}

void AdsrEnvelope::TransitionTo_(State_t toState) {

	m_state = toState;

	switch (toState) {
	case state_att:
		m_filt.SetFreq(m_attFreq);
		break;
	case state_dec:
		m_filt.SetFreq(m_decFreq);
		m_filt.SetVal(1.0f);
		break;
	case state_sus:
		m_filt.SetVal(m_susVal);
		break;
	case state_rel:
		m_filt.SetFreq(m_relFreq);
		break;
	case state_off:
		m_filt.SetVal(0.0f);
		break;
	}
}

sample_t AdsrEnvelope::StateAtt_() {
	
	// Overshoot
	float envVal = m_filt.ProcessLowpass(k_expOvershootf);

	if (envVal >= 1.0f) {
		TransitionTo_(state_dec);
		return 1.0f;
	}
	return envVal;
}

sample_t AdsrEnvelope::StateDec_() {
	
	float susVal = m_susVal;
	float envVal = m_filt.ProcessLowpass(m_susTarget);

	if (envVal <= susVal) {
		TransitionTo_(state_sus);
		return susVal;
	}
	return envVal;
}

sample_t AdsrEnvelope::StateSus_() {
	
	// Still want to filter, in case sustain param changes while already in sustain state
	// (Filter freq should still be set to decay value)
	
	float susVal = m_susVal;
	float envVal = m_filt.ProcessLowpass(susVal);

	return envVal;
}

sample_t AdsrEnvelope::StateRel_() {
	
	float envVal = m_filt.ProcessLowpass(1.0 - k_expOvershootf);

	if (envVal <= 0.0f) {
		TransitionTo_(state_off);
		return 0.0f;
	}
	return envVal;
}
