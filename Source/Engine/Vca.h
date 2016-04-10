/*
  ==============================================================================

    Vca.h
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
	void Process(Buffer& buf, eventBuf_t<gateEvent_t> const& gateEvents, Buffer const& env, bool bUseEnv, bool bClick);

private:
	double m_sampleRate;
	GateEnvelope m_ampEnv;
	Buffer m_ampEnvBuf;
};

}




#endif  // VCA_H_INCLUDED
