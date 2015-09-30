/*
  ==============================================================================

    MidiProcessorUnitTest.cpp
    Created: 17 Sep 2015 8:51:56am
    Author:  Joel

  ==============================================================================
*/

#include "MidiProcessorUnitTest.h"

#include "Engine/MidiProcessor.h"

using namespace juce;

//using MidiMessage = juce::MidiMessage;
//using MidiBuffer = juce::MidiBuffer;

namespace Test {

MidiProcessorUnitTest::MidiProcessorUnitTest()
	: UnitTest("MidiProcessor unit test")
{}

void MidiProcessorUnitTest::runTest() {

	beginTest("MidiProcessor unit test: basic case");
	{
		size_t nSamp = 512;
		Engine::MidiProcessor midiProc;
		MidiBuffer midiMessages;
		
		// Channel = 1 to 16
		uint8_t chan = 1;

		midiMessages.addEvent(MidiMessage::noteOn(chan, 60, uint8_t(100)), 100);
		midiMessages.addEvent(MidiMessage::noteOn(chan, 67, uint8_t(110)), 130);
		midiMessages.addEvent(MidiMessage::noteOn(chan, 72, uint8_t(120)), 150);

		// Remove middle note first
		midiMessages.addEvent(MidiMessage::noteOff(chan, 67), 170);
		midiMessages.addEvent(MidiMessage::noteOff(chan, 72), 200);
		midiMessages.addEvent(MidiMessage::noteOff(chan, 60), 250);

		eventBuf_t<gateEvent_t> gateEvents;
		eventBuf_t<uint8_t> noteEvents;
		eventBuf_t<uint8_t> velEvents;
		eventBuf_t<int> pitchBendEvents;

		midiProc.Process(nSamp, midiMessages, gateEvents, noteEvents, velEvents, pitchBendEvents);

		/*
		Expect:

		Time	Gate	Note	Vel
		100		on		60		100
		130		retrig	67		110
		150		retrig	72		120
		170		-		-		-
		200		retrig	60		100
		250		off		-		-

		*/

		
		if (midiMessages.getNumEvents() != 0) {
			std::cout << midiMessages.getNumEvents() << " skipped midi events!" << std::endl;
		}
		expect(midiMessages.getNumEvents() == 0);

		if (gateEvents.size() == 5) {
			expect(gateEvents[0] == Utils::timedEvent_t<gateEvent_t>(100, gateEvent_on));
			expect(gateEvents[1] == Utils::timedEvent_t<gateEvent_t>(130, gateEvent_retrig));
			expect(gateEvents[2] == Utils::timedEvent_t<gateEvent_t>(150, gateEvent_retrig));
			expect(gateEvents[3] == Utils::timedEvent_t<gateEvent_t>(200, gateEvent_retrig));
			expect(gateEvents[4] == Utils::timedEvent_t<gateEvent_t>(250, gateEvent_off));
		}
		else {
			std::cout << "gateEvents.size() == " << gateEvents.size() << std::endl;
			for (auto it = gateEvents.begin(); it != gateEvents.end(); ++it) {
				std::cout << "    " << it->time << ", " << int(it->ev) << "\n";
			}
		}
		expect(gateEvents.size() == 5);

		if (noteEvents.size() == 4) {
			expect(noteEvents[0] == Utils::timedEvent_t<uint8_t>(100, 60));
			expect(noteEvents[1] == Utils::timedEvent_t<uint8_t>(130, 67));
			expect(noteEvents[2] == Utils::timedEvent_t<uint8_t>(150, 72));
			expect(noteEvents[3] == Utils::timedEvent_t<uint8_t>(200, 60));
		}
		else {
			std::cout << "noteEvents.size() == " << noteEvents.size() << std::endl;
			for (auto it = noteEvents.begin(); it != noteEvents.end(); ++it) {
				std::cout << "    " << it->time << ", " << int(it->ev) << "\n";
			}
		}
		expect(noteEvents.size() == 4);

		if (velEvents.size() == 4) {
			expect(velEvents[0] == Utils::timedEvent_t<uint8_t>(100, 100));
			expect(velEvents[1] == Utils::timedEvent_t<uint8_t>(130, 110));
			expect(velEvents[2] == Utils::timedEvent_t<uint8_t>(150, 120));
			expect(velEvents[3] == Utils::timedEvent_t<uint8_t>(200, 100));
		}
		else {
			std::cout << "velEvents.size() == " << velEvents.size() << std::endl;
			for (auto it = velEvents.begin(); it != velEvents.end(); ++it) {
				std::cout << "    " << it->time << ", " << int(it->ev) << "\n";
			}
		}
		expect(velEvents.size() == 4);
		
		expect(pitchBendEvents.size() == 0);
		
		// TODO: test sustain pedal
		// TODO: test legato/retrig
		// TODO: test "legato on sustain pedal" mode

		// TODO: test pitch bend

		// TODO: test atypical situations:
		// noteOff with velocity
		// noteOff via noteOn with zero velocity
		// notes on various channels
		// add note already playing
		// remove note that doesn't exist
	}
	

	
}

}

