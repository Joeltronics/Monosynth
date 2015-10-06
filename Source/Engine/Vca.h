/*
  ==============================================================================

    Vca.h
    Created: 5 Oct 2015 9:14:56pm
    Author:  Joel

  ==============================================================================
*/

#ifndef VCA_H_INCLUDED
#define VCA_H_INCLUDED

#include "JuceHeader.h"
#include "Types.h"
#include "Envelope.h"

namespace Engine {

class Vca {
public:

	Vca() : m_sampleRate(0.0) {}
	~Vca() {}

	void PrepareToPlay(double sampleRate, int samplesPerBlock);
	void Process(Buffer& buf, eventBuf_t<gateEvent_t> const& gateEvents);

private:
	double m_sampleRate;
	GateEnvelope m_ampEnv;
};

}




#endif  // VCA_H_INCLUDED
