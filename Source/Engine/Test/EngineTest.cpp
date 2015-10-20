/*
  ==============================================================================

    EngineTest.cpp
    Created: 5 Oct 2015 7:36:27pm
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

#include "EngineTest.h"

#include "JuceHeader.h"

#include "Utils/TimestampedEvent.h"

#include "Engine/Engine.h"

namespace Test {

String const k_filename("Monosynth_Test.wav");

EngineTest::EngineTest()
	: UnitTest("Engine test")
{}

void EngineTest::runTest() {

	beginTest("Engine Test");
	{
		
		
		// Note: there are hard-coded numbers below depending on these 2 values!
		const double sampleRate = 44100.0;
		const size_t blockSize = 256;

		const size_t nChan = 1;

		// Total length = 1 second, as a multiple of block size (rounded up)
		const size_t nBlocks = std::ceil(44100.0 / blockSize);

		const uint8_t midiChan = 1;

		std::cout << "Constructing SynthEngine" << std::endl;

		SynthEngine engine;

		std::cout << "Calling PrepareToPlay" << std::endl;

		engine.PrepareToPlay(sampleRate, blockSize);

		juce::AudioSampleBuffer buf(nChan, blockSize);
		
		Utils::eventBuf_t<juce::MidiMessage> midiMsgs;

		midiMsgs.push_back(timedEvent_t<juce::MidiMessage>(1000, MidiMessage::noteOn(midiChan, 60, uint8_t(100))));
		midiMsgs.push_back(timedEvent_t<juce::MidiMessage>(33000, MidiMessage::noteOff(midiChan, 60, uint8_t(100))));

		/*
		midiMessages.addEvent(MidiMessage::noteOn(midiChan, 60, uint8_t(100)), 100);
		midiMessages.addEvent(MidiMessage::noteOn(midiChan, 67, uint8_t(110)), 130);
		midiMessages.addEvent(MidiMessage::noteOn(midiChan, 72, uint8_t(120)), 150);

		// Remove middle note first
		midiMessages.addEvent(MidiMessage::noteOff(midiChan, 67), 170);
		midiMessages.addEvent(MidiMessage::noteOff(midiChan, 72), 200);
		midiMessages.addEvent(MidiMessage::noteOff(midiChan, 60), 250);
		*/

		std::cout << "Opening wav file to write" << std::endl;

		File ofile(File::getCurrentWorkingDirectory().getChildFile(k_filename));
		
		if (ofile.existsAsFile())
			ofile.deleteFile();

		WavAudioFormat format;
		FileOutputStream* fos = ofile.createOutputStream();
		ScopedPointer<AudioFormatWriter> writer = format.createWriterFor(fos, sampleRate, nChan, 16, NULL, 0);


		std::cout << "Processing" << std::endl;

		float minVal = 0.0f;
		float maxVal = 0.0f;

		for (size_t n = 0; n < nBlocks; ++n) {

			juce::MidiBuffer midiMessages;

			switch (n) {
			case 10:
				midiMessages.addEvent(MidiMessage::noteOn(midiChan, 60, uint8_t(100)), 100);
				break;
			case 37:
				midiMessages.addEvent(MidiMessage::noteOn(midiChan, 67, uint8_t(40)), 206);
				break;
			case 62:
				// Test multiple messages in same buf
				midiMessages.addEvent(MidiMessage::noteOff(midiChan, 67), 35);
				midiMessages.addEvent(MidiMessage::noteOn(midiChan, 72, uint8_t(120)), 189);
				break;
			case 89:
				midiMessages.addEvent(MidiMessage::noteOff(midiChan, 72), 189);
				break;
			case 130:
				midiMessages.addEvent(MidiMessage::noteOff(midiChan, 60), 35);
				break;
			default:
				break;
			}

			engine.Process(buf, midiMessages);

			juce::Range<float> minMax = juce::FloatVectorOperations::findMinAndMax(buf.getReadPointer(0), blockSize);

			minVal = std::min(minVal, minMax.getStart());
			maxVal = std::max(maxVal, minMax.getEnd());

			writer->writeFromAudioSampleBuffer(buf, 0, blockSize);
		}

		std::cout << "Complete!" << std::endl;
		std::cout << "Output sample range: (" << minVal << ", " << maxVal << ")" << std::endl;
	}
}

} // namespace Test