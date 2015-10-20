/*
  ==============================================================================

    MidiProcessor.h
    Created: 7 Sep 2015 2:05:07pm
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

#ifndef MIDIPROCESSOR_H_INCLUDED
#define MIDIPROCESSOR_H_INCLUDED

#include "Types.h"

#include <deque>

namespace Engine {

// ***** NoteQueue *****

class NoteQueue {
public:
	NoteQueue();
	~NoteQueue();

	midiNote_t Add(midiNote_t note);
	midiNote_t Remove(midiNote_t note); // syntactic sugar for Remove(uint8_t); inlined below
	midiNote_t Remove(uint8_t noteNum);

	midiNote_t GetCurrNote(); // inlined below
	void Clear(); // inlined below

private:
	bool RemoveIfPresent_(uint8_t noteNum); /// Returns true if note removed

	std::deque<midiNote_t> m_queue;
};

// Inline functions:

inline midiNote_t NoteQueue::Remove(midiNote_t note) { return Remove(note.n); }

inline void NoteQueue::Clear() { m_queue.clear(); }

inline midiNote_t NoteQueue::GetCurrNote() {
	return (
		m_queue.empty() ?
		midiNote_t(0, 0) :
		m_queue.back());
}

// ***** MidiProcessor *****

class MidiProcessor {
public:
	MidiProcessor();
	~MidiProcessor();
	
	void Process(
		/*in*/ size_t nSamp,
		/*inOut*/ juce::MidiBuffer& midiMessages,
		/*out*/ eventBuf_t<gateEvent_t>& gateEvents,
		/*out*/ eventBuf_t<uint8_t>& noteEvents,
		/*out*/ eventBuf_t<uint8_t>& velEvents,
		/*out*/ eventBuf_t<uint16_t>& pitchBendEvents);

	void Clear();

private:

	NoteQueue m_noteQueue;

	midiNote_t m_prevNote;

	bool m_bRetrig;
	bool m_bSusPedal;
	std::vector<uint8_t> m_susNotes; /// Notes that have been noteOff'ed but are still being played because of sustain pedal

};
}




#endif  // MIDIPROCESSOR_H_INCLUDED
