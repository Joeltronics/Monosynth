/*
  ==============================================================================

    Lfo.h
    Created: 18 Jan 2016 8:14:00pm
    Author:  Joel

  ==============================================================================
*/

#ifndef LFO_H_INCLUDED
#define LFO_H_INCLUDED

#include "Types.h"

namespace Engine {

class Lfo {
public:
	Lfo();
	~Lfo() {}

	// Output LFOs have range (-1,1)

	// Used for LFO1
	// Note: buf should already contain scaled pitch data!
	void ProcessWithKbTracking(
		eventBuf_t<gateEvent_t> gateEvents /*in*/,
		sample_t freq /*in*/,
		waveform_t wave /*in*/,
		Buffer& buf /*inOut*/);

	// Used for LFO2
	void Process(
		eventBuf_t<gateEvent_t> gateEvents /*in*/,
		sample_t freq /*in*/,
		waveform_t wave /*in*/,
		float shape /*in*/,
		Buffer& outBuf /*out*/);
	
	void PrepareToPlay(double sampleRate, int samplesPerBlock);

private:
	
	double m_sampleRate;
	sample_t m_phase;

}; // class Lfo

} // namespace Engine



#endif  // LFO_H_INCLUDED
