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

enum waveform_t {
	waveShape_saw = 0,
	waveShape_pwm,
	waveShape_tri,
	waveShape_squ50,
	waveShape_pulse25
};

class Oscillator {
public:
	Oscillator();
	Oscillator(sample_t initPhase);
	~Oscillator();

	// TODO: randomize phase
	void PrepareToPlay(double sampleRate, int /*samplesPerBlock*/) { m_sampleRate = sampleRate; }

	void ProcessFromFreq(Buffer& audioBuf /*out*/, Buffer& freqPhaseBuf /*inout*/, waveform_t wave /*in*/, float shape /*in*/);
	
	void ProcessSynced(Buffer& audioBuf /*out*/, Buffer& freqBuf /*inout*/, Buffer const& syncPhaseBuf /*in*/, waveform_t wave /*in*/, float shape /*in*/);
	
	void ProcessSub(Buffer& audioBuf /*out*/, Buffer const& phaseBuf /*in*/, waveform_t wave /*in*/, int octave);

private:
	float m_phase;
	double m_sampleRate;
	unsigned int m_phaseNum;
	float const mk_polyblepSize; // number of samples before and after transition to PolyBlep (default 1)
};

}

#endif  // OSCILLATOR_H_INCLUDED
