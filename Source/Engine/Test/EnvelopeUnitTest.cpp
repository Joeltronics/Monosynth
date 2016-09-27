/*
  ==============================================================================

    EnvelopeUnitTest.cpp
    Created: 28 Sep 2015 9:41:52pm
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

#include "EnvelopeUnitTest.h"

#include "Engine/Envelope.h"

#include "Utils/ApproxEqual.h"

namespace Test {

String const k_filename("Monosynth_EnvTest.wav");

EnvelopeUnitTest::EnvelopeUnitTest()
	: UnitTest("Envelope unit test")
{}

#define EXPEQ(A, B) \
	do { \
		bool bEq = Utils::ApproxEqual(A, B); \
		if (!bEq) { \
			std::cout << "Expected: " << #A << " == " << #B << std::endl;\
			std::cout << "Actual: " << A << " != " << B << std::endl;\
		} \
		expect(bEq); \
	} while(0)

#define EXPEQT(A, B, T) \
	do { \
		bool bEq = Utils::ApproxEqual(A, B, T); \
		if (!bEq) { \
			std::cout << "Expected: " << #A << " == " << #B << " within threshold " << T << std::endl;\
			std::cout << "Actual: " << A << " != " << B << std::endl;\
		} \
		expect(bEq); \
	} while(0)

#define EXPRANGE(n1, n2, val, T) \
	if (buf.IsVal()) {\
		EXPEQT(buf.GetVal(), val, T);\
	} \
	else {\
		for (size_t n = n1; n < n2; ++n) { \
			EXPEQT(buf.GetBuf()[n], val, T);\
		}\
	}

#define EXPSUS(n1, n2, val) EXPRANGE(n1, n2, val, 0.0001f)

#define EXPATT(n1, n2) \
	do { \
		float prevVal = buf[n1]; \
		for (size_t n = n1; n < n2; ++n) { \
			expect(buf[n] >= prevVal); \
			prevVal = buf[n]; \
		} \
		EXPEQT(buf[n2], 1.0f, 0.1f); \
	} while(0)

#define EXPDEC(n1, n2, susVal) \
	do { \
		float prevVal = buf[n1]; \
		for (size_t n = n1; n < n2; ++n) { \
			expect(buf[n] <= prevVal); \
			prevVal = buf[n]; \
		} \
		EXPEQT(buf[n1], 1.0f, 0.1f); \
		EXPEQT(buf[n2], susVal, 0.1f); \
	} while(0)

#define EXPREL(n1, n2) \
	do { \
		float prevVal = buf[n1]; \
		for (size_t n = n1; n < n2; ++n) { \
			expect(buf[n] <= prevVal); \
			prevVal = buf[n]; \
		} \
		EXPEQT(buf[n2], 0.0f, 0.1f); \
	} while(0)

static bool Eq(float a, float b) {
	bool bEq = Utils::ApproxEqual(a, b);

	return bEq;
}

void EnvelopeUnitTest::runTest() {

	// TODO: this isn't going to work once GateEnvelope isn't just on/off!

	beginTest("GateEnvelope unit test");
	{
		size_t nSamp = 512;
		Engine::GateEnvelope env;
		eventBuf_t<gateEvent_t> gateEvents;
		BufferOrVal buf(nSamp);

		env.PrepareToPlay(44100.0, nSamp);

		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(50, gateEvent_on_trig));
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(100, gateEvent_legato));
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(150, gateEvent_retrig));
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(200, gateEvent_off));
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(300, gateEvent_on_trig));
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(400, gateEvent_retrig));

		env.Process(gateEvents, buf);

		EXPRANGE(0, 49, 0.0f, 0.0001f);
		EXPRANGE(50, 71, 1.0f, 1.0f);
		EXPRANGE(72, 99, 1.0f, 0.4f);
		EXPRANGE(100, 199, 1.0f, 0.0001f);
		EXPRANGE(200, 221, 0.0f, 1.0f);
		EXPRANGE(222, 249, 0.0f, 0.4f);
		EXPRANGE(250, 299, 0.0f, 0.0001f);
		EXPRANGE(300, 321, 1.0f, 1.0f);
		EXPRANGE(322, 349, 1.0f, 0.4f);
		EXPRANGE(350, nSamp-1, 1.0f, 0.0001f);

		gateEvents.clear();
		env.Process(gateEvents, buf);

		EXPRANGE(0, nSamp-1, 1.0f, 0.0001f);

		gateEvents.clear();
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(50, gateEvent_off));
		env.Process(gateEvents, buf);

		EXPRANGE(0, 49, 1.0f, 0.0001f);
		EXPRANGE(50, 71, 0.0f, 1.0f);
		EXPRANGE(72, 99, 0.0f, 0.4f);
		EXPRANGE(100, nSamp-1, 0.0f, 0.0001f);

		gateEvents.clear();
		env.Process(gateEvents, buf);

		EXPRANGE(0, nSamp-1, 0.0f, 0.0001f);
	}

	beginTest("AdsrEnvelope unit test");
	{
		size_t sampPerBlock = 8192;
		size_t nChan = 1;
		double sampleRate = 44100.0;

		Engine::AdsrEnvelope env;
		eventBuf_t<gateEvent_t> gateEvents;
		juce::AudioSampleBuffer juceBuf(nChan, sampPerBlock);
		BufferOrVal buf(sampPerBlock);

		std::cout << "Opening wav file to write" << std::endl;

		File ofile(File::getCurrentWorkingDirectory().getChildFile(k_filename));

		if (ofile.existsAsFile())
			ofile.deleteFile();

		WavAudioFormat format;
		FileOutputStream* fos = ofile.createOutputStream();
		ScopedPointer<AudioFormatWriter> writer = format.createWriterFor(fos, sampleRate, nChan, 16, NULL, 0);

		std::cout << "Processing" << std::endl;

		double att = 200.0123 / sampleRate; // ~200 samples
		double dec = 100.0825 / sampleRate; // ~100 samples
		double rel = 300.01 / sampleRate; // ~300 samples

		/*
		Expected shape:

        1.0__ 
		        /\
		0.4__  /  \_____
		      /         \
		0.0__/           \__
		     |20|10|   |30|     (10s of samples)
		*/

		env.PrepareToPlay(sampleRate, sampPerBlock);

		std::cout << "Attack: " << att << "\n"
			      << "Decay: " << dec << "\n"
			      << "Release: " << rel << std::endl;

		env.SetVals(att, dec, 0.4f, rel);

		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(500, gateEvent_on_trig));
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(1000, gateEvent_legato));
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(1500, gateEvent_retrig));
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(2000, gateEvent_off));
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(3000, gateEvent_on_trig));
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(4000, gateEvent_retrig));

		env.Process(gateEvents, buf);

		juce::FloatVectorOperations::copy(juceBuf.getWritePointer(0), buf.GetBufPtr(), sampPerBlock);
		writer->writeFromAudioSampleBuffer(juceBuf, 0, sampPerBlock);

		/*
		EXPRANGE(0, 499, 0.0f, 0.0001f); // 0-500 off
		EXPATT(500, 699); // 500-700 attack
		EXPDEC(700, 799, 0.4f); // 700-800 decay
		EXPSUS(810, 1499, 0.4f); // 800-1500 sustain
		EXPATT(1500, 1699); // 150-170 attack
		EXPDEC(1700, 1799, 0.4f); // 1700-1800 decay
		EXPSUS(1810, 1999, 0.4f); // 1800-2000 sustain
		EXPREL(2000, 2299); // 2000-2300 release
		EXPRANGE(2300, 2999, 1.0f, 0.4f); // 2300-3000 off
		EXPATT(3000, 3199); // 3000-3200 attack
		EXPDEC(3200, 3309, 0.4f); // 3200-3300 decay
		EXPSUS(3310, 4009, 0.4f); // 3300-4000 sustain
		EXPATT(4000, 4209); // 4000-4200 attack
		EXPDEC(4200, 4299, 0.4f); // 4200-4300 decay
		EXPSUS(4310, sampPerBlock - 1, 0.4f); // 430-end sustain
		*/

		gateEvents.clear();

		// change sustain value
		env.SetVals(att, dec, 0.8f, rel);
		
		env.Process(gateEvents, buf);

		buf.ConvertValToBuf(); // not that efficient, but good enough for test
		juce::FloatVectorOperations::copy(juceBuf.getWritePointer(0), buf.GetBufPtr(), sampPerBlock);
		writer->writeFromAudioSampleBuffer(juceBuf, 0, sampPerBlock);

		// Not going to be exact because of quirks with changing sustain value during sustain phase
		EXPRANGE(150, sampPerBlock - 1, 0.8f, 0.1f);

		gateEvents.clear();
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(50, gateEvent_off));
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(100, gateEvent_on_legato));
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(150, gateEvent_off));
		env.Process(gateEvents, buf);

		buf.ConvertValToBuf();
		juce::FloatVectorOperations::copy(juceBuf.getWritePointer(0), buf.GetBufPtr(), sampPerBlock);
		writer->writeFromAudioSampleBuffer(juceBuf, 0, sampPerBlock);

		// TODO
		//EXPRANGE(0, 49, 1.0f, 0.0001f);
		//EXPRANGE(50, 71, 0.0f, 1.0f);
		//EXPRANGE(72, 99, 0.0f, 0.4f);
		//EXPRANGE(100, nSamp - 1, 0.0f, 0.0001f);

		gateEvents.clear();
		env.Process(gateEvents, buf);

		buf.ConvertValToBuf();
		juce::FloatVectorOperations::copy(juceBuf.getWritePointer(0), buf.GetBufPtr(), sampPerBlock);
		writer->writeFromAudioSampleBuffer(juceBuf, 0, sampPerBlock);

		EXPRANGE(0, sampPerBlock - 1, 0.0f, 0.0001f);
	}
}

}