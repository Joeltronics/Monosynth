/*
  ==============================================================================

    Vca.cpp
    Created: 5 Oct 2015 9:14:56pm
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

#include "Vca.h"
#include "Utils/Logger.h"

namespace Engine {

void Vca::PrepareToPlay(double sampleRate, int samplesPerBlock) {
	m_sampleRate = sampleRate;
	m_ampEnv.PrepareToPlay(sampleRate, samplesPerBlock);

	m_ampEnvBuf.SetBuffer();
	m_ampEnvBuf.GetBuf().Resize(samplesPerBlock, true);
}

void Vca::Process(Buffer& buf, eventBuf_t<gateEvent_t> const& gateEvents, BufferOrVal const& env, bool bUseEnv, bool bClick) {

	DEBUG_ASSERT(m_sampleRate > 0.0);

	if (bUseEnv) {
		buf *= env;
	}
	else {
		
		size_t const nSamp = buf.GetLength();
		
		if (nSamp > m_ampEnvBuf.GetAllocLength()) {
			LOG(juce::String::formatted(
				"WARNING: Unexpected buffer size increase, was %u, now %u - reallocating from audio thread!",
				m_ampEnvBuf.GetAllocLength(), nSamp));
		}

		if (m_ampEnvBuf.GetLength() != nSamp) {
			m_ampEnvBuf.Resize(nSamp, false);
		}
		
		// FIXME: this doesn't process when bUseEnv, so if switching bUseEnv while note is held down, note may disappear!
		// (This will probably get fixed when eventBuf_t gets fixed)
		m_ampEnv.Process(gateEvents, m_ampEnvBuf);

		// TODO: click (if bClick)

		buf *= m_ampEnvBuf;
	}
}

}