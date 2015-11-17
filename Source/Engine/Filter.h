/*
  ==============================================================================

    Filter.h
    Created: 19 Oct 2015 10:35:38pm
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

#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

#include "Types.h"

#include "Utils/OnePole.h"

// Include files needed by externals so they don't get imported into EngineExt namespace instead
#include <cmath>
#include <algorithm>
#include <cassert> 

namespace EngineExt {
#include "Engine/Externals/TransistorLadderFilter.hpp"
#include "Engine/Externals/DiodeLadderFilter.hpp"
}

namespace Engine {

enum filterModel_t {
	filterModel_none = 0,
	filterModel_transLadder,
	filterModel_diodeLadder,
	filterModel_ota
};

// This class wraps external filter code
class Filter {
public:

	Filter() :
		m_sampleRate(0.0),
		m_model(filterModel_transLadder)
	{}
	
	~Filter() {}

	void Filter::PrepareToPlay(double sampleRate, int /*samplesPerBlock*/) { m_sampleRate = sampleRate;	}
	
	// freqCv = normalized freq (0-0.5)
	// res = in range [0, 1]
	void Process(Buffer& buf /*inOut*/, Buffer& freqCv /*in*/, double res /*in*/, filterModel_t model /*in*/);

private:
	
	double m_sampleRate;
	filterModel_t m_model;
	
	EngineExt::TransistorLadderFilter transFilt;
	EngineExt::DiodeLadderFilter diodeFilt;

}; // class Filter
} // namespace Engine



#endif  // FILTER_H_INCLUDED
