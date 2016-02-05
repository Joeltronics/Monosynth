/*
  ==============================================================================

    Oscillator.cpp
    Created: 5 Oct 2015 9:14:41pm
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

#include "Oscillators.h"
#include "Utils/DspUtils.h"

namespace Engine {

/*
This oscillator uses PolyBLEPs for anti-aliasing

Polybleps aren't that great - but they're cheap to compute, so can afford
to also oversample. And the combination of Polyblep + oversampling is
good.

Polyblep size (i.e. number of samples on each side of transition) can be
increased (normally it's 1) - increasing it reduces the top end a bit, but
with oversampling, the HF loss is all above the audible range.
*/

namespace Detail {

// Both of these assume upward step - simply negate for downward step
static float DiffPolyBlepBeforeStep(sample_t x) {
	// x should be negative
	return  0.5f*(x*x) + x + 0.5f;
}

static float DiffPolyBlepAfterStep(sample_t x) {
	// x should be positive
	return -0.5f*(x*x) + x - 0.5f;
}

/**
 * @param[in] phase: in range [0,1)
 * @param[in] freq: normalized, i.e. phase increment per sample
 */
static float WaveshapeSaw(sample_t phase, sample_t freq) {
	
	if (phase < freq) {
		// First sample after transition
		sample_t pb = Detail::DiffPolyBlepAfterStep(phase / freq);
		return phase - 0.5f - pb;
	}
	else if (phase > (1.0f - freq)) {
		// Last sample before transition
		sample_t pb = Detail::DiffPolyBlepBeforeStep((phase - 1.0f) / freq);
		return phase - 0.5f - pb;
	}
	else {
		// Middle
		return phase - 0.5f;
	}
}

/**
* @param[in] phase: in range [0,1)
* @param[in] freq: normalized, i.e. phase increment per sample
*/
static float WaveshapeRect(sample_t phase, sample_t freq, sample_t duty) {

	if (phase > (1.0f - freq)) {
		// Last sample before downward transition
		return 0.5f - Detail::DiffPolyBlepBeforeStep((phase - 1.0f) / freq);
	}
	else if (phase < freq) {
		// First sample after downward transition
		return -0.5f - Detail::DiffPolyBlepAfterStep(phase / freq);
	}
	else if (phase < duty && phase > (duty - freq)) {
		// Last sample before upward transition
		return -0.5f + Detail::DiffPolyBlepBeforeStep((phase - duty) / freq);
	}
	else if (phase >= duty && phase < (duty + freq)) {
		// First sample after upward transition
		return 0.5f + Detail::DiffPolyBlepAfterStep((phase - duty) / freq);
	}
	else {
		// Middle
		return (phase >= duty ? 0.5f : -0.5f);
	}
}

/**
* @param[in] phase: in range [0,1)
* @param[in] freq: normalized, i.e. phase increment per sample
*/
static float WaveshapeTri(sample_t phase, sample_t freq) {
	// TODO: polyblep
	return abs(phase - 0.5f) * 2.0f - 0.5f;
}

} // namespace Detail

Oscillator::Oscillator() :
	m_sampleRate(0.0),
	m_phase(0.0f),
	m_phaseNum(0),
	m_polyblepSize(1.0f)
{}

Oscillator::Oscillator(sample_t initPhase) :
	m_sampleRate(0.0),
	m_phase(initPhase),
	m_phaseNum(0),
	m_polyblepSize(1.0f)
{}

Oscillator::~Oscillator() {}

// TODO: randomize phase
void Oscillator::PrepareToPlay(double sampleRate, int /*samplesPerBlock*/) {
	m_sampleRate = sampleRate;

	if (sampleRate > 100e3f)
		m_polyblepSize = 2.f;
	else
		m_polyblepSize = 1.f;
}

void Oscillator::ProcessFromFreq(Buffer& audioBuf, Buffer& freqPhaseBuf, waveform_t wave, float shape) {
	DEBUG_ASSERT(m_sampleRate > 0.0);
	DEBUG_ASSERT(audioBuf.GetLength() == freqPhaseBuf.GetLength());

	// TODO: phaseIncr should actually be average of prev and next freq
	// (half-sample delay)
	// will need memory of previous

	float* audio = audioBuf.Get();
	float* freqPhase = freqPhaseBuf.Get();

	if (wave == waveShape_saw) {
		for (size_t n = 0; n < audioBuf.GetLength(); ++n) {

			// This is actually next freq (because we increment phase at end of loop)
			sample_t freq = freqPhase[n];

			audio[n] = Detail::WaveshapeSaw(m_phase, freq * m_polyblepSize);
			freqPhase[n] = m_phase;

			m_phase = fmod(m_phase + freq, 1.0f);
		}
	}
	else if (wave == waveShape_pwm) {
		// TODO: if pw changes and it causes wave to flip, polyBlep!
		float pw = (shape * 0.5f) + 0.5f;
		for (size_t n = 0; n < audioBuf.GetLength(); ++n) {

			// This is actually next freq (because we increment phase at end of loop)
			sample_t freq = freqPhase[n];

			audio[n] = Detail::WaveshapeRect(m_phase, freq * m_polyblepSize, pw);
			freqPhase[n] = m_phase;

			m_phase = fmod(m_phase + freq, 1.0f);
		}
	}
	else if (wave == waveShape_tri) {
		for (size_t n = 0; n < audioBuf.GetLength(); ++n) {
			
			// This is actually next freq (because we increment phase at end of loop)
			sample_t freq = freqPhase[n];

			audio[n] = Detail::WaveshapeTri(m_phase, freq * m_polyblepSize);
			freqPhase[n] = m_phase;

			m_phase = fmod(m_phase + freq, 1.0f);
		}
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

	// TODO: polyblep
	// not sure what to do here, because we don't have freq information at this point
	// could either hold on to second buffer, or better, roll all oscillators together
	
	float* audio = audioBuf.Get();
	if (wave == waveShape_tri) {
		for (size_t n = 0; n < audioBuf.GetLength(); ++n) {
			audio[n] = abs(audio[n] - 0.5f) * 2.0f - 0.5f;
		}
	}
	else if (wave == waveShape_pulse25 ||
			 wave == waveShape_squ50)
	{
		float pw = (wave == waveShape_squ50 ? 0.50f : 0.25f);
		for (size_t n = 0; n < audioBuf.GetLength(); ++n) {
			audio[n] = ((audio[n] >= pw) ? 0.5f : -0.5f);
		}
	}
	else {
		DEBUG_ASSERT(false);
	}
}

} // namespace Engine