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
	~Lfo();

	void PrepareToPlay(double sampleRate, int samplesPerBlock);

	void Reset();

	// Output LFOs have range (-1,1)

	/* ProcessHighFreq
	 * Processes anti-aliased LFO
	 *
	 * freq: normalized to sample rate (0-1)
	 */
	void ProcessHighFreq(
		eventBuf_t<gateEvent_t> gateEvents /*in*/,
		sample_t shape /*in*/,
		sample_t freq /*in*/,
		Buffer& buf /*out*/);

	/* ProcessHighFreqWithKbTracking
	 * Processes anti-aliased LFO, with keyboard tracking
	 *
	 * freq: normalized to sample rate (0-1)
	 * buf:
	 *   input: scaled pitch data
	 *   output: LFO signal
	 */
	void ProcessHighFreqWithKbTracking(
		eventBuf_t<gateEvent_t> gateEvents /*in*/,
		sample_t shape /*in*/,
		sample_t freq /*in*/,
		Buffer& buf /*inOut*/);

	/* ProcessLowFreq
	 * Processes LFO; will alias at high frequencies
	 *
	 * freq: normalized to sample rate (0-1)
	 */
	void ProcessLowFreq(
		eventBuf_t<gateEvent_t> gateEvents /*in*/,
		sample_t shape /*in*/,
		sample_t freq /*in*/,
		Buffer& outBuf /*out*/);

private:
	
	void ProcessLfo_(
		eventBuf_t<gateEvent_t> gateEvents /*in*/,
		sample_t shape /*in*/,
		sample_t freq /*in*/,
		Buffer& outBuf /*out*/);

	double m_sampleRate;
	sample_t m_phase;

}; // class Lfo

} // namespace Engine



#endif  // LFO_H_INCLUDED
