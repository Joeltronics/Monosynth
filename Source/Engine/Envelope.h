/*
  ==============================================================================

    Envelope.h
    Created: 28 Sep 2015 9:16:52pm
    Author:  Joel

  ==============================================================================
*/

#ifndef ENVELOPE_H_INCLUDED
#define ENVELOPE_H_INCLUDED

#include "Types.h"
#include "Utils/OnePole.h"

namespace Engine {

class Envelope {
public:
	Envelope() {}
	~Envelope() {}

	virtual void Process(eventBuf_t<gateEvent_t> /*in*/, Buffer& /*out*/) = 0;
	virtual void PrepareToPlay(double sampleRate, int samplesPerBlock) = 0;

private:

};

class GateEnvelope : public Envelope {
public:
	GateEnvelope();
	~GateEnvelope() {}

	void Process(eventBuf_t<gateEvent_t> /*in*/, Buffer& /*out*/) override;
	void PrepareToPlay(double sampleRate, int samplesPerBlock) override;

private:
	Utils::OnePole m_filt;
	gateEvent_t m_lastGate;
};

class AdsrEnvelope : public Envelope {
public:
	AdsrEnvelope();
	~AdsrEnvelope() {}

	void Process(eventBuf_t<gateEvent_t> /*in*/, Buffer& /*out*/) override;
	void PrepareToPlay(double sampleRate, int samplesPerBlock) override;

private:
	sample_t m_memory;
};

}

#endif  // ENVELOPE_H_INCLUDED
