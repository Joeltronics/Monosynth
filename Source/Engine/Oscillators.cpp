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
#include "Utils/ApproxEqual.h"
#include "Utils/Logger.h"

using namespace Engine;

/*
This oscillator uses PolyBLEPs for anti-aliasing

Polybleps aren't that great - but they're cheap to compute, so can afford
to also oversample. And the combination of Polyblep + oversampling is
good.

Polyblep size (i.e. number of samples on each side of transition) can be
increased (normally it's 1) - increasing it reduces the top end a bit, but
with oversampling, the HF loss is all above the audible range.
*/

// peak-peak amplitude (squ & saw are 1.0)
const float k_triWaveAmpl = 1.5f;

namespace Detail {

// Both of these assume upward step - simply negate for downward step
constexpr float DiffPolyBlepBeforeStep(sample_t x) {
	// x should be negative
	return  0.5f*(x*x) + x + 0.5f;
}

constexpr float DiffPolyBlepAfterStep(sample_t x) {
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
		sample_t pb = DiffPolyBlepAfterStep(phase / freq);
		return phase - 0.5f - pb;
	}
	else if (phase > (1.0f - freq)) {
		// Last sample before transition
		sample_t pb = DiffPolyBlepBeforeStep((phase - 1.0f) / freq);
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
* @param[in] mod: mod value - typically [0,0.5] but can be any range. 0 or 1 is regular saw, 0.5 is octave up
*/
static float WaveshapeSaw(sample_t phase, sample_t freq, sample_t mod) {
	sample_t secondPhase = phase + mod;
	secondPhase = fmod(secondPhase, 1.0f);
	if (secondPhase < 0.0f) secondPhase += 1.0f;
	return 0.5f * (WaveshapeSaw(phase, freq) + WaveshapeSaw(secondPhase, freq));
}

/**
* @param[in] phase: in range [0,1)
* @param[in] freq: normalized, i.e. phase increment per sample
* @param[in] duty: duty cycle, 0-1
*/
static float WaveshapeRect(sample_t phase, sample_t freq, sample_t duty) {

	if (phase > (1.0f - freq)) {
		// Last sample before downward transition
		return 0.5f - DiffPolyBlepBeforeStep((phase - 1.0f) / freq);
	}
	else if (phase < freq) {
		// First sample after downward transition
		return -0.5f - DiffPolyBlepAfterStep(phase / freq);
	}
	else if (phase < duty && phase > (duty - freq)) {
		// Last sample before upward transition
		return -0.5f + DiffPolyBlepBeforeStep((phase - duty) / freq);
	}
	else if (phase >= duty && phase < (duty + freq)) {
		// First sample after upward transition
		return 0.5f + DiffPolyBlepAfterStep((phase - duty) / freq);
	}
	else {
		// Middle
		return (phase >= duty ? 0.5f : -0.5f);
	}
}

// TODO: might want to apply k_triWaveAmpl in mixer instead, so ring mod isn't affected
const float k_doubleTriWaveAmpl = 2.f*k_triWaveAmpl;
const float k_halfTriWaveAmpl = 0.5f*k_triWaveAmpl;

/**
* @param[in] phase: in range [0,1)
* @param[in] freq: normalized, i.e. phase increment per sample
*/
static float WaveshapeTri(sample_t phase) {
	return abs(phase - 0.5f) * k_doubleTriWaveAmpl - k_halfTriWaveAmpl;
}

/**
* @param[in] phase: in range [0,1)
* @param[in] freq: normalized, i.e. phase increment per sample
* @param[in] mod: mod value - typically [0,0.5] but can be any range. 0 or 1 is regular tri, 0.5 is octave up
*/
static float WaveshapeTri(sample_t phase, sample_t mod) {
	
	sample_t tri = abs(phase - 0.5f) * 2.0f;
	
	// Now tri has range [0,1.0)
	
	tri -= mod;

	// Now tri has range:
	//   Mod 0.0: [0.0,1.0)
	//   Mod 0.5: [-0.5,0.5)
	//   Mod 1.0: [-1.0,0.0)

	tri = fabs(tri);

	// Now tri has range:
	//   Mod 0.0: [0.0,1.0)
	//   Mod 0.5: [0.0,0.5)
	//   Mod 1.0: [0.0,1.0)

	return tri * k_triWaveAmpl - k_halfTriWaveAmpl;
}

static void ProcessOsc_(
	Buffer& outBuf, /*out*/
	sample_t& rPhase, /*inout*/
	Buffer const& freqBuf, /*in*/
	sample_t polyblepSize, /*in*/
	waveform_t wave /*in*/)
{
	size_t const nSamp = outBuf.GetLength();

	DEBUG_ASSERT(freqBuf.GetLength() == nSamp);

	// TODO: phase increment should actually be average of prev and next freq
	// (half-sample delay)
	// will need memory of previous

	float const* pFreq = freqBuf.GetConst();
	float* pAudio = outBuf.Get();

	/*
	A note about using a stack var (or even register) intead of accessing the
	reference every time:

	Normally this would be a pointless optimization to make. But these vars will
	accessed about a million times per second (across all the places we make this
	optimization in the 3 processing functions), so it's worth the very slight
	speedup. It's possible the compiler would make this optimization anyway, but
	given that this part is performance critical, it's worth doing this to
	virtually guarantee it happens.
	
	Any resulting bugs should be easy to catch - if the phase doesn't get updated,
	then there would be obvious audio problems (and unless doing something stupid
	below, there shouldn't be any obscure corner cases).

	As for using the "register" keyword, I don't know if it actually does anything
	in modern C++ (it will even be deprecated in C++17), but might as well use it.
	*/
	register sample_t phase = rPhase;

	if (wave == waveShape_saw) {
		// TODO: shape control
		for (size_t n = 0; n < nSamp; ++n) {

			sample_t f = pFreq[n]; // This is actually next freq (because we increment phase at end of loop)
			pAudio[n] = Detail::WaveshapeSaw(phase, f * polyblepSize);
			phase = fmod(phase + f, 1.0f);
		}
	}
	else if (wave == waveShape_pwm) {
		for (size_t n = 0; n < nSamp; ++n) {

			sample_t f = pFreq[n]; // next freq (see above)
			pAudio[n] = Detail::WaveshapeRect(phase, f * polyblepSize, 0.5f);
			phase = fmod(phase + f, 1.0f);
		}
	}
	else if (wave == waveShape_tri) {
		// TODO: since this doesn't use PolyBlep, could use Utils::FreqToPhase and then vectorize WaveshapeTri
		for (size_t n = 0; n < nSamp; ++n) {

			sample_t f = pFreq[n]; // next freq (see above)
			pAudio[n] = Detail::WaveshapeTri(phase);
			phase = fmod(phase + f, 1.0f);
		}
		// TODO: shape control (foldback)
	}
	else {
		DEBUG_ASSERT(false);
	}

	rPhase = phase;
}

static void ProcessOscPhaseOut_(
	Buffer& outBuf, /*out*/
	Buffer& phaseBuf, /*out*/
	sample_t& rPhase, /*inout*/
	Buffer const& freqBuf, /*in*/
	sample_t polyblepSize, /*in*/
	waveform_t wave, /*in*/
	BufferOrVal const& shape /*in*/)
{
	size_t const nSamp = outBuf.GetLength();

	DEBUG_ASSERT(freqBuf.GetLength() == nSamp);
	DEBUG_ASSERT(phaseBuf.GetLength() == nSamp);

	// TODO: phase increment should actually be average of prev and next freq (see above)

	float const* pFreq = freqBuf.GetConst();
	float* pAudio = outBuf.Get();
	float* pPhase = phaseBuf.Get();

	bool bShapeMod = !shape.IsVal();

	// See above for comments about these optimizations

	register sample_t phase = rPhase;

	if (wave == waveShape_saw) {
		if (bShapeMod) {
			sample_t const* pShape = shape.GetBufConstPtr();
			for (size_t n = 0; n < nSamp; ++n) {
				sample_t f = pFreq[n];  // This is actually next freq (because we increment phase at end of loop)
				sample_t sh = pShape[n] * 0.5f;
				pAudio[n] = Detail::WaveshapeSaw(phase, f * polyblepSize, sh);
				pPhase[n] = phase;
				phase = fmod(phase + f, 1.0f);
			}
		}
		else {
			sample_t sh = shape.GetVal() * 0.5f;
			for (size_t n = 0; n < nSamp; ++n) {
				sample_t f = pFreq[n]; // next freq (see above)
				pAudio[n] = Detail::WaveshapeSaw(phase, f * polyblepSize, sh);
				pPhase[n] = phase;
				phase = fmod(phase + f, 1.0f);
			}
		}
	}
	else if (wave == waveShape_pwm) {
		// TODO: if pw changes and it causes wave to flip, polyBlep!
		if (bShapeMod) {
			sample_t const* pPw = shape.GetBufConstPtr();
			for (size_t n = 0; n < nSamp; ++n) {
				sample_t f = pFreq[n]; // next freq (see above)
				sample_t pw = (pPw[n] * 0.5f) + 0.5f;
				pAudio[n] = Detail::WaveshapeRect(phase, f * polyblepSize, pw);
				pPhase[n] = phase;
				phase = fmod(phase + f, 1.0f);
			}
		}
		else {
			sample_t pw = (shape.GetVal() * 0.5f) + 0.5f;
			for (size_t n = 0; n < nSamp; ++n) {
				sample_t f = pFreq[n]; // next freq (see above)
				pAudio[n] = Detail::WaveshapeRect(phase, f * polyblepSize, pw);
				pPhase[n] = phase;
				phase = fmod(phase + f, 1.0f);
			}
		}
	}
	else if (wave == waveShape_tri) {
		// TODO: since this doesn't use PolyBlep, could use Utils::FreqToPhase and then vectorize WaveshapeTri
		if (bShapeMod) {
			//sample_t sh = shape.GetVal() * 0.5f;
			sample_t const* pShape = shape.GetBufConstPtr();
			for (size_t n = 0; n < nSamp; ++n) {
				sample_t f = pFreq[n]; // next freq (see above)
				sample_t sh = pShape[n] * 0.5f;
				pAudio[n] = Detail::WaveshapeTri(phase, sh);
				pPhase[n] = phase;
				phase = fmod(phase + f, 1.0f);
			}
		}
		else {
			sample_t sh = shape.GetVal() * 0.5f;
			for (size_t n = 0; n < nSamp; ++n) {
				sample_t f = pFreq[n]; // next freq (see above)
				pAudio[n] = Detail::WaveshapeTri(phase, sh);
				pPhase[n] = phase;
				phase = fmod(phase + f, 1.0f);
			}
		}
	}
	else {
		DEBUG_ASSERT(false);
	}

	rPhase = phase;
}

// TODO
#if 0
static void ProcessOscSynced_(
	Buffer& outBuf, /*out*/
	sample_t& rPhase, /*inout*/
	Buffer const& rSyncPhaseBuf, /*in*/
	Buffer const& freqBuf, /*in*/
	sample_t polyblepSize, /*in*/
	waveform_t wave /*in*/)
{}
#endif

static void ProcessSub_(
	Buffer& phaseInAudioOut /*inout*/,
	sample_t& rPhase /*inout*/,
	size_t& rPhaseNum /*inout*/,
	Buffer const& masterOscFreqBuf /*in*/,
	sample_t polyblepSize, /*in*/
	waveform_t wave /*in*/,
	int octave /*in*/)
{
	DEBUG_ASSERT(phaseInAudioOut.GetLength() == masterOscFreqBuf.GetLength());
	
	size_t const nSamp = phaseInAudioOut.GetLength();

	DEBUG_ASSERT(octave < 0);
	unsigned int const div = exp2(abs(octave));

	float* pBuf = phaseInAudioOut.Get();

	// 1. Unwrap phase
	{
		// See above for comments about these optimizations
		register sample_t phase = rPhase;
		register size_t phaseNum = rPhaseNum;

		for (size_t n = 0; n < nSamp; ++n) {

			// If zero crossing, increment phaseNum
			if (pBuf[n] < phase)
				phaseNum = ((phaseNum + 1) % div);

			phase = pBuf[n];

			pBuf[n] += float(phaseNum);
		}

		rPhase = phase;
		rPhaseNum = phaseNum;

		phaseInAudioOut /= float(div);
	}

	// 2. Waveshape

	if (wave == waveShape_tri) {
		for (size_t n = 0; n < nSamp; ++n) {
			pBuf[n] = WaveshapeTri(pBuf[n]);
		}
	}
	else if (wave == waveShape_pulse25 || wave == waveShape_squ50) {
		float const pw = (wave == waveShape_squ50 ? 0.50f : 0.25f);
		float const* pFreq = masterOscFreqBuf.GetConst();
		
		// Freq is of master osc, so it corresponds to 2x or 4x freq. Divide by that amount.
		float freqPolyblepMultiplier = polyblepSize / float(div);

		for (size_t n = 0; n < nSamp; ++n) {
			pBuf[n] = WaveshapeRect(pBuf[n], pFreq[n] * freqPolyblepMultiplier, pw);
		}
	}
	else {
		DEBUG_ASSERT(false);
	}
}

} // namespace Detail

// TODO: randomize initial phases!
Oscillators::Oscillators() :
	m_sampleRate(0.0),
	m_osc1Phase(0.0f),
	m_osc2Phase(0.0f),
	m_subPhaseNum(0),
	m_polyblepSize(1.0f),
	m_bOsc1BufPopulated(false),
	m_bOsc2BufPopulated(false),
	m_tempBufUsage(TempBufUsage::none)
{}

Oscillators::~Oscillators() {}

void Oscillators::PrepareToPlay(double sampleRate, int samplesPerBlock) {
	m_sampleRate = sampleRate;

	ReallocBufs_(samplesPerBlock);

	if (sampleRate > 100e3f)
		m_polyblepSize = 2.f;
	else
		m_polyblepSize = 1.f;
}

void Oscillators::ReallocBufs_(size_t nSamp) {

	DEBUG_ASSERT(m_osc1Buf.GetLength() == m_osc2Buf.GetLength());
	DEBUG_ASSERT(m_osc1Buf.GetLength() == m_tempBuf.GetLength());
	size_t currLen = m_osc1Buf.GetLength();

	DEBUG_ASSERT(m_osc1Buf.GetAllocLength() == m_osc2Buf.GetAllocLength());
	DEBUG_ASSERT(m_osc1Buf.GetAllocLength() == m_tempBuf.GetAllocLength());
	size_t allocLen = m_osc1Buf.GetAllocLength();

	if (nSamp != currLen || nSamp != allocLen) {
		// Always resize
		m_osc1Buf.Resize(nSamp, true);
		m_osc2Buf.Resize(nSamp, true);
		m_tempBuf.Resize(nSamp, true);
	}
}

void Oscillators::ResizeBufsNoRealloc_(size_t nSamp) {
	
	DEBUG_ASSERT(m_osc1Buf.GetLength() == m_osc2Buf.GetLength());
	DEBUG_ASSERT(m_osc1Buf.GetLength() == m_tempBuf.GetLength());
	size_t currLen = m_osc1Buf.GetLength();

	DEBUG_ASSERT(m_osc1Buf.GetAllocLength() == m_osc2Buf.GetAllocLength());
	DEBUG_ASSERT(m_osc1Buf.GetAllocLength() == m_tempBuf.GetAllocLength());
	size_t allocLen = m_osc1Buf.GetAllocLength();
	
	// If already the right size, no need to do anything
	if (nSamp != currLen) {

		if (nSamp > allocLen) {
			LOG(juce::String::formatted(
				"WARNING: Unexpected buffer size increase, was %u, now %u - reallocating from audio thread!",
				currLen, nSamp));
		}

		m_osc1Buf.Resize(nSamp, false);
		m_osc2Buf.Resize(nSamp, false);
		m_tempBuf.Resize(nSamp, false);
	}

	m_bOsc1BufPopulated = false;
	m_bOsc2BufPopulated = false;
	m_tempBufUsage = TempBufUsage::none;
}

void Oscillators::Process(
	Buffer& outBuf /*out*/,
	Buffer& freqBuf1 /*in*/,
	Buffer& freqBuf2 /*in*/,
	BufferOrVal const& shape /*in*/,
	Oscillators::Params const& params /*in*/)
{
	size_t const nSamp = outBuf.GetLength();
	
	ResizeBufsNoRealloc_(nSamp);

	// TODO: in some cases (osc level zero, ring off, sync off), don't need osc to be computed at all
	// If sync, we don't need to compute entire buf, can just compute phase buf

	bool const bSync = params.bSync;

	// Process osc 1 first
	ProcessOsc1_(outBuf, freqBuf1, shape, params);
	ProcessOsc2_(outBuf, freqBuf2, params);

	ProcessSub_(outBuf, freqBuf1, params);

	ProcessRingMod_(outBuf, params.ringGain*4.f);
}

void Oscillators::ProcessRingMod_(Buffer& buf, float ampl) {
	
	if (Utils::ApproxEqual(ampl, 0.f)) return;

	DEBUG_ASSERT(m_bOsc1BufPopulated && m_bOsc2BufPopulated);

	// This is the last we need to use osc2Buf, so can use it for ring mod
	m_osc2Buf *= m_osc1Buf;
	
	buf.AddWithMultiply(m_osc2Buf, ampl);
}

// Will populate m_osc1Buf
void Oscillators::ProcessOsc1_(Buffer& outBuf, Buffer const& freqBuf, BufferOrVal const& shape, Params const& params) {

	DEBUG_ASSERT(m_sampleRate > 0.0);
	DEBUG_ASSERT(!m_bOsc1BufPopulated);
	DEBUG_ASSERT(m_tempBufUsage == TempBufUsage::none);
	
	Detail::ProcessOscPhaseOut_(
		m_osc1Buf,
		m_tempBuf,
		m_osc1Phase,
		freqBuf,
		m_polyblepSize,
		params.osc1Wave,
		shape);

	m_bOsc1BufPopulated = true;
	m_tempBufUsage = TempBufUsage::osc1Phase;

	outBuf.AddWithMultiply(m_osc1Buf, params.osc1Gain);
}

// Will populate m_osc2Buf
void Oscillators::ProcessOsc2_(Buffer& outBuf, Buffer const& freqBuf, Params const& params) {
	
	DEBUG_ASSERT(m_sampleRate > 0.0);
	DEBUG_ASSERT(!m_bOsc2BufPopulated);

	if (params.bSync) {
		DEBUG_ASSERT(m_tempBufUsage == TempBufUsage::osc1Phase);

#if 0
		Detail::ProcessOscSynced_(
			m_osc2Buf,
			m_osc2Phase,
			m_tempBuf /*rSyncPhaseBuf*/,
			freqBuf,
			m_polyblepSize,
			params.osc2Wave);
#else
		Detail::ProcessOsc_(
			m_osc2Buf,
			m_osc2Phase,
			freqBuf,
			m_polyblepSize,
			params.osc2Wave);
#endif
	}
	else
	{
		Detail::ProcessOsc_(
			m_osc2Buf,
			m_osc2Phase,
			freqBuf,
			m_polyblepSize,
			params.osc2Wave);
	}

	outBuf.AddWithMultiply(m_osc2Buf, params.osc2Gain);

	m_bOsc2BufPopulated = true;
}

void Oscillators::ProcessSub_(Buffer& outBuf, Buffer const& oscFreqBuf, Params const& params) {

	DEBUG_ASSERT(m_sampleRate > 0.0);
	DEBUG_ASSERT(m_tempBufUsage == TempBufUsage::osc1Phase);

	Detail::ProcessSub_(
		m_tempBuf,
		m_subPhase,
		m_subPhaseNum,
		oscFreqBuf,
		m_polyblepSize,
		params.subOscWave,
		params.subOscOct);
	
	m_tempBufUsage = TempBufUsage::subAudio;
	outBuf.AddWithMultiply(m_tempBuf, params.subGain);
}
