/*
  ==============================================================================

    Vca.cpp
    Created: 5 Oct 2015 9:14:56pm
    Author:  Joel

  ==============================================================================
*/

#include "Vca.h"

namespace Engine {

void Vca::PrepareToPlay(double sampleRate, int samplesPerBlock) {
	m_sampleRate = sampleRate;
	m_ampEnv.PrepareToPlay(sampleRate, samplesPerBlock);
}

void Vca::Process(Buffer& buf, eventBuf_t<gateEvent_t> const& gateEvents) {

	DEBUG_ASSERT(m_sampleRate > 0.0);

	// TODO: more features

	Buffer ampEnvBuf(buf.GetLength());
	m_ampEnv.Process(gateEvents, ampEnvBuf);

	buf *= ampEnvBuf;
}

}