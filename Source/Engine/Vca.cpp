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