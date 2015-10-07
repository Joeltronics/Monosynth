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

	// TODO: this is just temporary implementation (an aliasing sawtooth)
	audioBuf = freqPhaseBuf - 0.5f;
}

void Oscillator::ProcessSynced(Buffer& audioBuf, Buffer& freqBuf, Buffer const& syncPhaseBuf, waveform_t wave, float shape) {
	DEBUG_ASSERT(m_sampleRate > 0.0);

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