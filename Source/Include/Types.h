/*
  ==============================================================================

    Types.h
    Created: 7 Sep 2015 5:16:07pm
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

#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED


// Juce includes
#include "AppConfig.h"
#include "modules/juce_audio_basics/juce_audio_basics.h"

#include "Utils/Types.h"

#include <vector>

using sample_t = Utils::sample_t;
using Buffer = Utils::Buffer;
template<typename T> using timedEvent_t = Utils::timedEvent_t<T>;
template<typename T> using eventBuf_t = Utils::eventBuf_t<T>;

uint8_t const k_defaultMidiVel = 100;

// GateBuf
enum gateEvent_t {
	gateEvent_off = 0,
	gateEvent_on_trig,
	gateEvent_on_legato,
	gateEvent_legato,
	gateEvent_retrig,

	// on_trig and on_legato are both triggering a note from off, but depending on if
	// in legato or retrig mode. Both should behave like a note trigger, but one slight
	// difference: on_trig will always reset envelope to zero, while on_legato won't.
	// Usually this doesn't matter because envelope is already at zero, but it will be
	// different if triggering new note while still in release phase of previous note
	// (similar to vintage Minimoog envelope behavior)
};

// MIDI types:

struct midiNote_t {
	uint8_t n; // Note number
	uint8_t v; // Velocity

	midiNote_t() :
		n(0), v(0) {}
	midiNote_t(uint8_t note) :
		n(note), v(k_defaultMidiVel) {}
	midiNote_t(uint8_t note, uint8_t vel) :
		n(note), v(vel) {}

	midiNote_t(juce::MidiMessage& m) {
		if (m.isNoteOnOrOff()) {
			n = uint8_t(m.getNoteNumber());
			v = uint8_t(m.getVelocity());
		}
		else {
			n = 0;
			v = 0;
		}
	}
};

static bool operator==(midiNote_t const& lhs, midiNote_t const& rhs) {
	return (lhs.n == rhs.n && lhs.v == rhs.v);
}

static bool operator!=(midiNote_t const& lhs, midiNote_t const& rhs) {
	return !(lhs == rhs);
}

namespace Engine {
	// Used for both VCO and LFO
	enum waveform_t {
		waveShape_saw = 0,
		waveShape_sawDown,
		waveShape_sawTriSaw,
		waveShape_pwm,
		waveShape_squ50,
		waveShape_pulse25,
		waveShape_tri,
		waveShape_sin,
		waveShape_triSinSqu,
		waveShape_sampleHold,
		waveShape_envelope,
		waveShape_envelopeDown
	};
}

#endif  // TYPES_H_INCLUDED
