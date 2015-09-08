/*
  ==============================================================================

    MidiProcessor.h
    Created: 7 Sep 2015 2:05:07pm
    Author:  Joel

  ==============================================================================
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
		/*out*/ eventBuf_t<int>& pitchBendEvents);

	void Clear();

private:

	NoteQueue m_noteQueue;

	bool m_bRetrig;
	bool m_bSusPedal;
	std::vector<uint8_t> m_susNotes; /// Notes that have been noteOff'ed but are still being played because of sustain pedal

};
}




#endif  // MIDIPROCESSOR_H_INCLUDED
