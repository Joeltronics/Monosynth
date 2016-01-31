/*
  ==============================================================================

    Lfo.cpp
    Created: 18 Jan 2016 8:14:00pm
    Author:  Joel

  ==============================================================================
*/

#include "Lfo.h"

#include "Params.h"

#include "Utils/DspUtils.h"
#include "Utils/ApproxEqual.h"

using namespace Engine;

namespace Detail {

	// Output LFOs have range (-1,1)

	static sample_t WaveshapeSawUp(sample_t phase) {
		return (2.f*phase) - 1.f;
	}

	static sample_t WaveshapeSawDown(sample_t phase) {
		return 1.f - (2.f*phase);
	}

	static sample_t WaveshapeSqu(sample_t phase) {
		return (phase >= 0.5f ? 1.f : -1.f);
	}

	static sample_t WaveshapeTri(sample_t phase) {
		return abs(phase - 0.5f) * 4.0f - 1.f;
	}

	static sample_t WaveshapeSin(sample_t phase) {
		// TODO: analog-style tanh (approximated) sine shaping
		return WaveshapeTri(phase);
	}

	static sample_t WaveshapeSawTriSaw(sample_t phase, sample_t shape) {
		
		if (phase < shape) {
			sample_t upPhase = Utils::ReverseInterp(0.f, shape, phase);
			return WaveshapeSawUp(upPhase);
		}
		else {
			sample_t downPhase = Utils::ReverseInterp(shape, 1.f, phase);
			return WaveshapeSawDown(downPhase);
		}
	}

} // namespace Detail

Lfo::Lfo() :
	m_sampleRate(0.0)
{}

Lfo::~Lfo() {}

void Lfo::PrepareToPlay(double sampleRate, int /*samplesPerBlock*/) {
	m_sampleRate = sampleRate;
}

void Lfo::Reset() {
	m_phase = 0.f;
}

void Lfo::ProcessHighFreq(
	eventBuf_t<gateEvent_t> gateEvents /*in*/,
	waveform_t wave /*in*/,
	sample_t freq /*in*/,
	Buffer& buf /*inOut*/)
{
	DEBUG_ASSERT(m_sampleRate > 0.0);
	// TODO: antialiasing
	ProcessLfo_(gateEvents, wave, freq, buf);
}

void Lfo::ProcessHighFreqWithKbTracking(
	eventBuf_t<gateEvent_t> gateEvents /*in*/,
	waveform_t wave /*in*/,
	sample_t freq /*in*/,
	Buffer& buf /*inOut*/)
{
	DEBUG_ASSERT(m_sampleRate > 0.0);
	// TODO: actually implement this
	ProcessHighFreq(gateEvents, wave, freq, buf);
}

/* paramA:
 *   attack (0-1) if waveShape_envelope
 *   normalized freq (0-1) otherwise
 * 
 * paramB:
 *   decay (0-1) if waveShape_envelope
 *   smoothing (0-1) if waveShape_sampleHold
 *   attack (0-1) otherwise
 */
void Lfo::ProcessLowFreq(
	eventBuf_t<gateEvent_t> gateEvents /*in*/,
	waveform_t wave /*in*/,
	sample_t freq /*in*/,
	Buffer& outBuf /*out*/)
{
	DEBUG_ASSERT(m_sampleRate > 0.0);
	ProcessLfo_(gateEvents, wave, freq, outBuf);
}

void Lfo::ProcessLfo_(
	eventBuf_t<gateEvent_t> gateEvents /*in*/,
	waveform_t wave /*in*/,
	sample_t freq /*in*/,
	Buffer& outBuf /*out*/)
{
	size_t nSamp = outBuf.GetLength();
	float* wp = outBuf.Get();

	// Calculate phase
	for (size_t n = 0; n < nSamp; ++n) {
		m_phase += freq;
		m_phase = fmod(m_phase, 1.0f);
		wp[n] = m_phase;
	}

	// Waveshape
	switch (wave) {
	case waveShape_squ50:
		for (size_t n = 0; n < nSamp; ++n) wp[n] = Detail::WaveshapeSqu(wp[n]);
		break;
	case waveShape_saw:
		for (size_t n = 0; n < nSamp; ++n) wp[n] = Detail::WaveshapeSawUp(wp[n]);
		break;
	case waveShape_sawDown:
		for (size_t n = 0; n < nSamp; ++n) wp[n] = Detail::WaveshapeSawDown(wp[n]);
		break;
	case waveShape_tri:
		for (size_t n = 0; n < nSamp; ++n) wp[n] = Detail::WaveshapeTri(wp[n]);
		break;
	case waveShape_sin:
		for (size_t n = 0; n < nSamp; ++n) wp[n] = Detail::WaveshapeSin(wp[n]);
		break;
	default:
		// TODO: log error
		outBuf.Clear();
		break;
	}
}

void Lfo::ProcessSampHold(
	eventBuf_t<gateEvent_t> gateEvents /*in*/,
	sample_t rate /*in*/,
	sample_t smoothing /*in*/,
	Buffer& outBuf /*out*/)
{
	// TODO
	outBuf.Clear();
}

