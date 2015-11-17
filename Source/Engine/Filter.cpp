/*
  ==============================================================================

    Filter.cpp
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

#include "Filter.h"
#include "Utils/DspUtils.h"
#include "Utils/ApproxEqual.h"
#include "Utils/Logger.h"

namespace Engine {

const double k_diodeResHpfCutoff_Hz = 40.0;

void Filter::Process(Buffer& buf, double fc, double res, filterModel_t model) {
	DEBUG_ASSERT(m_sampleRate > 0.0);

	if (model != m_model) {
		transFilt.reset();
		diodeFilt.reset();
	}

	const size_t nSamp = buf.GetLength();

	float const* inBuf = buf.GetConst();
	float* outBuf = buf.Get();

	switch (model)
	{
	case filterModel_none:
		break;

	case filterModel_transLadder:
		fc = Utils::Clip(fc, 0.001, 0.499);
		transFilt.transistorLadder(fc, res, inBuf, outBuf, nSamp);
		break;

	case filterModel_diodeLadder:
		// Diode filter freqs are normalized so Nyquist = 1.0, so scale freqs accordingly
		fc = fc * 2.0;
		fc = Utils::Clip(fc, 0.001, 0.999);
		diodeFilt.set_q(res);
		diodeFilt.set_feedback_hpf_cutoff(k_diodeResHpfCutoff_Hz / m_sampleRate * 2.0);

		for (size_t n = 0; n < nSamp; ++n)
			outBuf[n] = float(diodeFilt.tick(double(inBuf[n]), fc));

		break;

	case filterModel_ota:
		// TODO
		break;

	default:
		DEBUG_ASSERT(false);
		break;
	}


}

double Filter::FiltCvToFreq(double cvVal) const {
	
	const double valLog = Utils::Interp<double>(
		log10(20.0),
		log10(20000.0),
		cvVal);
	
	return pow(10.0, valLog);
}

} // namespace Engine