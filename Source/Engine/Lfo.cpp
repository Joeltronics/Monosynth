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
		// TODO: sine shaping
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

	static sample_t WaveshapeTriSinSqu(sample_t phase, sample_t shape) {
		sample_t tri = WaveshapeTri(phase);

		// TODO: distort
		
		return tri;
	}


} // namespace Detail

Lfo::Lfo() :
	m_sampleRate(0.0)
{}

void Lfo::PrepareToPlay(double sampleRate, int /*samplesPerBlock*/) {
	m_sampleRate = sampleRate;
}

// Used for LFO1
void Lfo::ProcessWithKbTracking(
	eventBuf_t<gateEvent_t> gateEvents /*in*/,
	sample_t freq /*in*/,
	waveform_t wave /*in*/,
	Buffer& buf /*inOut*/)
{
	DEBUG_ASSERT(m_sampleRate > 0.0);

	// TODO: antialiasing when frequency is high enough
	// TODO: pitch buffer

	size_t nSamp = buf.GetLength();
	float* wp = buf.Get();

	for (size_t n = 0; n < nSamp; ++n) {
		m_phase += freq;
		m_phase = fmod(m_phase, 1.0f);
		wp[n] = m_phase;
	}

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
	}
}

// Used for LFO2
void Lfo::Process(
	eventBuf_t<gateEvent_t> gateEvents /*in*/,
	sample_t freq /*in*/,
	waveform_t wave /*in*/,
	float shape /*in*/,
	Buffer& outBuf /*out*/)
{
	DEBUG_ASSERT(m_sampleRate > 0.0);

	size_t nSamp = outBuf.GetLength();
	float* wp = outBuf.Get();

	// Calculate phase
	for (size_t n = 0; n < nSamp; ++n) {
		m_phase += freq;
		m_phase = fmod(m_phase, 1.0f);
		wp[n] = m_phase;
	}

	// If shape knob is right at end, can use simpler waveshaper
	if (Utils::ApproxEqual(shape, 0.0f)) {
		switch (wave) {
		case waveform_t::waveShape_sawTriSaw: wave = waveform_t::waveShape_sawDown; break;
		case waveform_t::waveShape_triSinSqu: wave = waveform_t::waveShape_tri; break;
		default: break;
		}
	}
	else if (Utils::ApproxEqual(shape, 1.0f)) {
		switch (wave) {
		case waveform_t::waveShape_sawTriSaw: wave = waveform_t::waveShape_saw; break;
		case waveform_t::waveShape_triSinSqu: wave = waveform_t::waveShape_squ50; break;
		default: break;
		}
	}

	// TODO: S&H and envelope waveforms

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
	case waveShape_sawTriSaw:
		for (size_t n = 0; n < nSamp; ++n) wp[n] = Detail::WaveshapeSawTriSaw(wp[n], shape);
		break;
	case waveShape_triSinSqu:
		for (size_t n = 0; n < nSamp; ++n) wp[n] = Detail::WaveshapeTriSinSqu(wp[n], shape);
		break;
	case waveShape_envelope:
		// TODO
		break;
	case waveShape_envelopeDown:
		// TODO
		break;
	default:
		// TODO
		break;
	}
}




