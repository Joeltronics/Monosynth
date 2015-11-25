/*
  ==============================================================================

    MidiProcessor.cpp
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

#include "MidiProcessor.h"

#include "Types.h"

#include "Utils/Logger.h"

#include <vector>

namespace Engine {

// ***** NoteQueue *****

NoteQueue::NoteQueue() {}
NoteQueue::~NoteQueue() {}

midiNote_t NoteQueue::Add(midiNote_t note) {
	// If invalid note, do nothing
	if (note.n == 0) return GetCurrNote();

	// If vel = 0, this should be a NoteOff instead. However, we handle that logic at a higher level

	RemoveIfPresent_(note.n); // Should usually return false
	m_queue.push_back(note);
	return GetCurrNote();
}

midiNote_t NoteQueue::Remove(uint8_t noteNum) {
	if (noteNum != 0) RemoveIfPresent_(noteNum); // Should usually return true
	return GetCurrNote();
}

bool NoteQueue::RemoveIfPresent_(uint8_t noteNum) {
	for (std::deque<midiNote_t>::iterator it = m_queue.begin(); it != m_queue.end(); ++it) {
		if (it->n == noteNum) {
			m_queue.erase(it);
			return true;
		}
	}
	return false;
}

// ***** MidiProcessor *****

namespace Detail {
	static gateEvent_t GetGateEvent_(bool bPrevNoteOn, bool bNewNoteOn, bool bRetrig) {
		if (bNewNoteOn) {
			if (!bPrevNoteOn)
				return (bRetrig ? gateEvent_on_trig : gateEvent_on_legato);
			else
				return (bRetrig ? gateEvent_retrig : gateEvent_legato);
		}
		else {
			return gateEvent_off;
		}
	}

	static bool PushNewNote_(
		/*in*/ int time,
		/*in*/ midiNote_t newNote,
		/*in*/ bool bPrevNoteOn,
		/*in*/ bool bRetrig,
		/*inOut*/ eventBuf_t<gateEvent_t>& gateEvents,
		/*inOut*/ eventBuf_t<uint8_t>& noteEvents,
		/*inOut*/ eventBuf_t<uint8_t>& velEvents)
	{
		bool bNewNoteOn = (newNote.v > 0);
		gateEvents.push_back(timedEvent_t<gateEvent_t>(time, GetGateEvent_(bPrevNoteOn, bNewNoteOn, bRetrig)));

		// If it's a note-off, we don't push an event to note/vel so that the note won't sound weird during
		// the envelope decay
		if (bNewNoteOn) {
			noteEvents.push_back(timedEvent_t<uint8_t>(time, newNote.n));
			velEvents.push_back(timedEvent_t<uint8_t>(time, newNote.v));
		}

		return bNewNoteOn;
	}
}

MidiProcessor::MidiProcessor() :
	m_bRetrig(true),
	m_bSusPedal(false)
{}
MidiProcessor::~MidiProcessor() {}

void MidiProcessor::Clear() {
	m_noteQueue.Clear();
	m_susNotes.clear();
}

void MidiProcessor::Process(
	/*in*/ size_t /*nSamp*/,
	/*inOut*/ juce::MidiBuffer& midiMessages,
	/*out*/ eventBuf_t<gateEvent_t>& gateEvents,
	/*out*/ eventBuf_t<uint8_t>& noteEvents,
	/*out*/ eventBuf_t<uint8_t>& velEvents,
	/*out*/ eventBuf_t<uint16_t>& pitchBendEvents)
{
	bool bPrevNoteOn = (m_noteQueue.GetCurrNote().v > 0);

	gateEvents.clear();
	noteEvents.clear();
	velEvents.clear();
	pitchBendEvents.clear();

	juce::MidiBuffer skippedMidiMsgs;
	int time;
	juce::MidiMessage m;

	// TODO: mod wheel, aftertouch, etc
	// TODO: legato-on-sustain mode
	
	for (juce::MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);)
	{
		if (m.isNoteOn() || m.isNoteOff()) {

			midiNote_t newNote(m);
			
			bool bIsNoteOn = m.isNoteOn() && (newNote.v > 0);

			if (bIsNoteOn)
				LOG(juce::String::formatted("NoteOn: %u", m.getNoteNumber()));
			else
				LOG(juce::String::formatted("NoteOff: %u", m.getNoteNumber()));

			if (m_bSusPedal && !bIsNoteOn) {
				m_susNotes.push_back(newNote.n);
			}
			else {
				midiNote_t currNote = (bIsNoteOn ?
					m_noteQueue.Add(newNote) :
					m_noteQueue.Remove(newNote));

				// If the current note didn't change, do nothing
				// (e.g. if NoteOff on a note that isn't the current note, don't retrigger)
				if (currNote != m_prevNote)
					bPrevNoteOn = Detail::PushNewNote_(time, currNote, bPrevNoteOn, m_bRetrig, gateEvents, noteEvents, velEvents);

				m_prevNote = currNote;

				if (m_bSusPedal) {
					// erase-remove idiom
					m_susNotes.erase(
						std::remove(m_susNotes.begin(), m_susNotes.end(), newNote.n),
						m_susNotes.end());
				}
			}
		}
		else if (m.isAllNotesOff() || m.isAllSoundOff()) {
			// TODO: possibly treat these two differently?
			m_noteQueue.Clear();
			m_susNotes.clear();
			// Always assume previous note was on, to force noteOff gate event in case something went wrong
			Detail::PushNewNote_(time, midiNote_t(0, 0), true, m_bRetrig, gateEvents, noteEvents, velEvents);
			bPrevNoteOn = false;
		}
		else if (m.isPitchWheel()) {
			pitchBendEvents.push_back(timedEvent_t<uint16_t>(time, m.getPitchWheelValue()));
		}
		else if (m.isSustainPedalOn()) {
			m_bSusPedal = true;
		}
		else if (m.isSustainPedalOff()) {
			m_bSusPedal = false;
			
			midiNote_t currNote;
			for (std::vector<uint8_t>::iterator it = m_susNotes.begin(); it != m_susNotes.end(); ++it)
				currNote = m_noteQueue.Remove(uint8_t(*it));
			m_susNotes.clear();
			
			bPrevNoteOn = Detail::PushNewNote_(time, currNote, bPrevNoteOn, m_bRetrig, gateEvents, noteEvents, velEvents);
		}
		else {
			skippedMidiMsgs.addEvent(m, time);
		}
	}

	midiMessages.swapWith(skippedMidiMsgs);
}

}