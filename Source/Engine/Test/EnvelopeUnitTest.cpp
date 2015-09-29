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

#define EXPRANGE(n1, n2, val, T) \
	for (size_t n = n1; n < n2; ++n) { EXPEQT(buf[n], val, T); }

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
}

}