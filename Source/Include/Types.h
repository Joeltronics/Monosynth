/*
  ==============================================================================

    Types.h
    Created: 7 Sep 2015 5:16:07pm
    Author:  Joel

  ==============================================================================
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
	gateEvent_on,
	gateEvent_legato,
	gateEvent_retrig,
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

#endif  // TYPES_H_INCLUDED
