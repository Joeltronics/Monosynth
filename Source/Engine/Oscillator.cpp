/*
  ==============================================================================

    Oscillator.cpp
    Created: 5 Oct 2015 9:14:41pm
    Author:  Joel

  ==============================================================================
*/

#include "Oscillator.h"
#include "Utils/DspUtils.h"

namespace Engine {

Oscillator::Oscillator() :
	m_sampleRate(0.0),
	m_phase(0.0f),
	m_phaseNum(0)
{}

Oscillator::~Oscillator() {}

void Oscillator::ProcessFromFreq(Buffer& audioBuf, Buffer& freqPhaseBuf, waveform_t wave, float shape) {
	DEBUG_ASSERT(m_sampleRate > 0.0);
	DEBUG_ASSERT(audioBuf.GetLength() == freqPhaseBuf.GetLength());

	m_phase = Utils::FreqToPhase(freqPhaseBuf, m_phase);

	// TODO: these are just temporary (aliasing) implementations
	if (wave == waveShape_saw) {
		audioBuf = freqPhaseBuf - 0.5f;
	}
	else if (wave == waveShape_pwm) {
		
		float pw = (shape * 0.5f) + 0.5f;
		
		float* audio = audioBuf.Get();
		float const* phase = freqPhaseBuf.GetConst();

		for (size_t n = 0; n < audioBuf.GetLength(); ++n) {
			audio[n] = ((phase[n] >= pw) ? 0.5f : -0.5f);
		}
	}
	else if (wave == waveShape_tri) {
		audioBuf = freqPhaseBuf - 0.5f;
		juce::FloatVectorOperations::abs(audioBuf.Get(), audioBuf.GetConst(), audioBuf.GetLength());
		audioBuf -= 0.25f;
		audioBuf *= 2.0f;
	}
	else {
		DEBUG_ASSERT(false);
	}
}

void Oscillator::ProcessSynced(Buffer& audioBuf, Buffer& freqBuf, Buffer const& syncPhaseBuf, waveform_t wave, float shape) {
	DEBUG_ASSERT(m_sampleRate > 0.0);
	DEBUG_ASSERT(audioBuf.GetLength() == freqBuf.GetLength());
	DEBUG_ASSERT(audioBuf.GetLength() == syncPhaseBuf.GetLength());

	// TODO: sync
	Buffer phaseBuf(freqBuf);
	m_phase = Utils::FreqToPhase(phaseBuf, m_phase);

	// TODO
	audioBuf = phaseBuf - 0.5f;
}

void Oscillator::ProcessSub(Buffer& audioBuf, Buffer const& phaseBuf, waveform_t wave, int octave) {
	DEBUG_ASSERT(m_sampleRate > 0.0);
	DEBUG_ASSERT(audioBuf.GetLength() == phaseBuf.GetLength());

	// First unwrap phase
	{
		audioBuf = phaseBuf;
		float* p = audioBuf.Get();

		unsigned int div = exp2(abs(octave));

		for (size_t n = 0; n < audioBuf.GetLength(); ++n) {

			// If zero crossing, increment phaseNum
			if (p[n] < m_phase)
				m_phaseNum = ((m_phaseNum + 1) % div);

			m_phase = p[n];

			p[n] += float(m_phaseNum);
		}

		audioBuf /= float(div);
	}

	// Now waveshape

	if (wave == waveShape_tri) {
		audioBuf = audioBuf - 0.5f;
		juce::FloatVectorOperations::abs(audioBuf.Get(), audioBuf.GetConst(), audioBuf.GetLength());
		audioBuf -= 0.25f;
		audioBuf *= 2.0f;
	}
	else if (wave == waveShape_pulse25 ||
			 wave == waveShape_squ50)
	{
		float pw = (wave == waveShape_squ50 ? 0.50f : 0.25f);

		float* audio = audioBuf.Get();

		for (size_t n = 0; n < audioBuf.GetLength(); ++n) {
			audio[n] = ((audio[n] >= pw) ? 0.5f : -0.5f);
		}
	}
	else {
		DEBUG_ASSERT(false);
	}
}

} // namespace Engine