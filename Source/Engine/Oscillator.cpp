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

void Oscillator::ProcessFromFreq(Buffer& audioBuf, Buffer& freqPhaseBuf, waveform_t wave, float shape) {
	DEBUG_ASSERT(m_sampleRate > 0.0);

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
}

void Oscillator::ProcessSynced(Buffer& audioBuf, Buffer& freqBuf, Buffer const& syncPhaseBuf, waveform_t wave, float shape) {
	DEBUG_ASSERT(m_sampleRate > 0.0);

	// TODO: sync
	Buffer phaseBuf(freqBuf);
	m_phase = Utils::FreqToPhase(phaseBuf, m_phase);

	// TODO
	audioBuf = phaseBuf - 0.5f;
}

void Oscillator::ProcessSub(Buffer& audioBuf, Buffer const& phaseBuf, waveform_t wave, int octave) {
	DEBUG_ASSERT(m_sampleRate > 0.0);

	// TODO (this isn't even a sub!)
	audioBuf = phaseBuf - 0.5f;
}

} // namespace Engine