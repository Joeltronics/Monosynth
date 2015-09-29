/*
  ==============================================================================

    EnvelopeUnitTest.cpp
    Created: 28 Sep 2015 9:41:52pm
    Author:  Joel

  ==============================================================================
*/

#include "EnvelopeUnitTest.h"

#include "Engine/Envelope.h"

#include "Utils/ApproxEqual.h"

namespace Test {

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

#define EXPGT(A, B) \
	do { \
		bool bEq = (A >= B); \
		if (!bEq) { \
			std::cout << "Expected: " << #A << " >= " << #B << std::endl;\
			std::cout << "Actual: " << A << " < " << B << std::endl;\
		} \
		expect(bEq); \
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
		Buffer buf(nSamp);

		env.PrepareToPlay(44100.0, nSamp);

		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(50, gateEvent_on));
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(100, gateEvent_legato));
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(150, gateEvent_retrig));
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(200, gateEvent_off));
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(300, gateEvent_on));
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(400, gateEvent_retrig));

		env.Process(gateEvents, buf);

		for (size_t n = 0; n < 50; ++n) { EXPEQ(buf[n], 0.0f); }
		for (size_t n = 50; n < 72; ++n) { EXPEQT(buf[n], 1.0f, 1.0f); }
		for (size_t n = 72; n < 100; ++n) { EXPEQT(buf[n], 1.0f, 0.4f); }
		for (size_t n = 100; n < 200; ++n) { EXPEQ(buf[n], 1.0f); }
		for (size_t n = 200; n < 222; ++n) { EXPEQT(buf[n], 0.0f, 1.0f); }
		for (size_t n = 222; n < 250; ++n) { EXPEQT(buf[n], 0.0f, 0.4f); }
		for (size_t n = 250; n < 300; ++n) { EXPEQ(buf[n], 0.0f); }
		for (size_t n = 300; n < 322; ++n) { EXPEQT(buf[n], 1.0f, 1.0f); }
		for (size_t n = 322; n < 350; ++n) { EXPEQT(buf[322], 1.0f, 0.4f); }
		for (size_t n = 350; n < nSamp; ++n) { EXPEQ(buf[350], 1.0f); }

		gateEvents.clear();
		env.Process(gateEvents, buf);

		for (size_t n = 0; n < nSamp; ++n) { EXPEQ(buf[n], 1.0f); }

		gateEvents.clear();
		gateEvents.push_back(Utils::timedEvent_t<gateEvent_t>(50, gateEvent_off));

		env.Process(gateEvents, buf);

		for (size_t n = 0; n < 50; ++n) { EXPEQ(buf[n], 1.0f); }
		for (size_t n = 50; n < 72; ++n) { EXPEQT(buf[n], 0.0f, 1.0f); }
		for (size_t n = 72; n < 100; ++n) { EXPEQT(buf[n], 0.0f, 0.4f); }
		for (size_t n = 100; n < nSamp; ++n) { EXPEQ(buf[100], 0.0f); }

		gateEvents.clear();
		env.Process(gateEvents, buf);

		for (size_t n = 0; n < nSamp; ++n) { EXPEQ(buf[n], 0.0f); }
	}
}

}