/*
  ==============================================================================

    Engine.h
    Created: 7 Sep 2015 12:30:58pm
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

#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "JuceHeader.h"

#include "Types.h"

#include "Params.h"

#include "MidiProcessor.h"
#include "PitchProcessor.h"
#include "Envelope.h"
#include "Lfo.h"
#include "Oscillators.h"
#include "Vca.h"
#include "Filter.h"

namespace Utils {
	class IResampler;
}

class SynthEngine {
public:
	SynthEngine();
	~SynthEngine();

	std::vector<Param*> const& GetParamList() const;

	void PrepareToPlay(double sampleRate, int samplesPerBlock);

	void Process(juce::AudioSampleBuffer& buffer, juce::MidiBuffer& midiMessages);
	
private:
	
	void ReallocBufs_(size_t nSamp);
	void ResizeBufsNoRealloc_(size_t nSamp);

	void ProcessMod_(
		eventBuf_t<gateEvent_t> const& gateEvents /*in*/,
		Buffer& mod1Buf /*out*/,
		Buffer& mod2Buf /*out*/);
	
	void ProcessOscsAndMixer_(
		Buffer& mainBuf /*out*/,
		Buffer& osc1freq /*inout*/,
		Buffer& osc2freq /*inout*/);
	
	void ProcessFilter_(
		Buffer& buf /*inout*/,
		Buffer const& envBuf /*in*/,
		Buffer const& mod1Buf /*in*/,
		Buffer const& mod2Buf /*in*/);

	void DownsampleAndCopyToStereo_(
		Buffer const& overBuf /*in*/,
		juce::AudioSampleBuffer& juceBuf /*out*/) const;

	bool IsMod1HighFreq_() const;

	double m_sampleRateNative;
	size_t m_nOversample;
	double m_sampleRateOver;
    
   	uint8_t m_lastNote;

	juce::Random m_random;

	Engine::MidiProcessor m_midiProc;
	Engine::PitchProcessor m_pitchProc;

	Engine::AdsrEnvelope m_filtEnv;

	Engine::Lfo m_mod1;
	Engine::AdEnvelope m_mod2;

	Engine::Oscillators m_oscs;

	Engine::Filter m_filter;

	Engine::Vca m_vca;

	Utils::OnePole m_osc1ShapeCvFilt;
	Utils::OnePole m_filtFreqCvFilt;

	juce::ScopedPointer<Utils::IResampler> m_pResampler;

	ParamStruct m_params;

	// Buffers
	Buffer m_mainBuf;
	Buffer m_adsrBuf;
	Buffer m_mod1Buf;
	Buffer m_mod2Buf;
	Buffer m_freqPhaseBuf1;
	Buffer m_freqPhaseBuf2;
	Buffer m_filtCv;

	BufferOrVal m_osc1ShapeBuf;

	std::vector<std::reference_wrapper<Buffer>> m_rBufs;
};


#endif  // ENGINE_H_INCLUDED
