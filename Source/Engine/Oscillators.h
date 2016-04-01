/*
  ==============================================================================

    Oscillator.h
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

#ifndef OSCILLATOR_H_INCLUDED
#define OSCILLATOR_H_INCLUDED

#include "JuceHeader.h"
#include "Types.h"

namespace Engine {

class Oscillators {
public:

	struct Params {
		float osc1Gain, osc2Gain, subGain, ringGain;
		waveform_t osc1Wave, osc2Wave, subOscWave;
		float osc1Shape; // 0 to 1
		int subOscOct; // -1 or -2
		bool bSync;
		float crossMod; // 0 to 1
	};

	Oscillators();
	~Oscillators();

	void PrepareToPlay(double sampleRate, int samplesPerBlock);

	void Process(
		Buffer& outBuf /*out*/,
		Buffer& freqBuf1 /*in*/,
		Buffer& freqBuf2 /*in*/,
		Oscillators::Params const& params /*in*/);

private:

	void AllocateBufs_(size_t nSamp, bool bErrorIfDifferent);

	// ***** Processing *****

	// Will populate m_osc1Buf and populate m_tempBuf with osc 1 phase
	// If params has crossMod > 0, m_osc2Buf must be populated before this is called
	void ProcessOsc1_(Buffer& outBuf, Buffer const& freqBuf, Params const& params);

	// Will populate m_osc2Buf
	// If params has sync enabled, m_tempBuf must be populated with osc 1 phase before this is called
	void ProcessOsc2_(Buffer& outBuf, Buffer const& freqBuf, Params const& params);
	
	void ProcessSub_(Buffer& outBuf, Buffer const& oscFreqBuf, Params const& params);

	// m_osc1Buf and m_osc2Buf must be populated before this is called
	// This function is allowed to change the values of these
	void ProcessRingMod_(Buffer& outBuf, float ampl);

	// ***** Members *****

	enum class TempBufUsage {
		none,
		osc1Phase,
		subAudio
	};

	// Preallocated buffers
	Buffer m_osc1Buf;
	Buffer m_osc2Buf;
	Buffer m_tempBuf;
	
	// These are flags to make sure things get processed in the right order
	bool m_bOsc1BufPopulated;
	bool m_bOsc2BufPopulated;
	TempBufUsage m_tempBufUsage;

	double m_sampleRate;

	float m_osc1Phase;
	float m_osc2Phase;
	float m_subPhase;
	size_t m_subPhaseNum;
	
	float m_polyblepSize; // number of samples before and after transition to PolyBlep (default 1)
};

}

#endif  // OSCILLATOR_H_INCLUDED
