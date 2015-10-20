/*
  ==============================================================================

    OscillatorTest.cpp
    Created: 18 Oct 2015 8:02:01pm
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

#include "OscillatorTest.h"

#include "JuceHeader.h"

#include "Types.h"

#include "Engine/Oscillator.h"

namespace Test {

	String const k_filename("Monosynth_OscTest.wav");

	OscillatorTest::OscillatorTest()
		: UnitTest("Oscillator test")
	{}

	void OscillatorTest::runTest() {

		// TODO: test what happens if zero crossing are on exactly a sample! (e.g. normFreq = 1/16, initial pahse = 0)

		beginTest("Oscillator Test");
		{
			// Note: there are hard-coded numbers below depending on these 2 values!
			const double sampleRate = 44100.0;
			const size_t blockSize = 256;

			const size_t nChan = 2;

			// Total length = 1 second, as a multiple of block size (rounded up)
			const size_t nBlocks = std::ceil(44100.0 / blockSize);

			const uint8_t midiChan = 1;

			std::cout << "Constructing SynthEngine" << std::endl;

			Engine::Oscillator osc;
			Engine::Oscillator subOsc;

			std::cout << "Calling PrepareToPlay" << std::endl;

			osc.PrepareToPlay(sampleRate, blockSize);
			subOsc.PrepareToPlay(sampleRate, blockSize);

			juce::AudioSampleBuffer juceBuf(nChan, blockSize);
			Buffer buf(juceBuf.getWritePointer(0), blockSize);
			Buffer subBuf(juceBuf.getWritePointer(1), blockSize);
			Buffer freqPhaseBuf(blockSize);
			
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

				//Oscillator::ProcessFromFreq(Buffer& audioBuf, Buffer& freqPhaseBuf, waveform_t wave, float shape)

				Engine::waveform_t wave = Engine::waveShape_tri;
				float shape = 0.0f;
				float freq = 440.0f;

				switch (n)
				{
				case 0:
				case 1:
				case 2:
					wave = Engine::waveShape_saw;
					shape = 0.0f;
					freq = 440.0f;
					break;
				case 3:
					wave = Engine::waveShape_saw;
					shape = 0.0f;
					freq = 660.0f;
					break;
				case 4:
				case 5:
					wave = Engine::waveShape_pwm;
					shape = 0.0f;
					freq = 880.0f;
					break;
				case 6:
					wave = Engine::waveShape_pwm;
					shape = 0.33f;
					freq = 880.0f;
					break;
				case 7:
					wave = Engine::waveShape_pwm;
					shape = 0.90f;
					freq = 880.0f;
					break;
				}
				
				Engine::waveform_t subWave;
				switch (wave){
				case Engine::waveShape_saw: subWave = Engine::waveShape_pulse25; break;
				case Engine::waveShape_tri: subWave = Engine::waveShape_tri; break;
				case Engine::waveShape_pwm:
				default:					subWave = Engine::waveShape_squ50; break;
				}

				freqPhaseBuf.Set(freq / sampleRate);
				
				osc.ProcessFromFreq(buf, freqPhaseBuf, wave, shape);
				subOsc.ProcessSub(subBuf, freqPhaseBuf, subWave, -1);

				juce::Range<float> minMax = juce::FloatVectorOperations::findMinAndMax(buf.GetConst(), blockSize);

				minVal = std::min(minVal, minMax.getStart());
				maxVal = std::max(maxVal, minMax.getEnd());

				writer->writeFromAudioSampleBuffer(juceBuf, 0, blockSize);
			}

			std::cout << "Complete!" << std::endl;
			std::cout << "Output sample range: (" << minVal << ", " << maxVal << ")" << std::endl;
		}
	}
} // namespace Test