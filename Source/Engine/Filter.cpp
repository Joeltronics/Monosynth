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

void Filter::Process(Buffer& buf, Buffer& freqCv, double res, filterModel_t model, uint8_t nPoles) {
	DEBUG_ASSERT(m_sampleRate > 0.0);
	DEBUG_ASSERT(buf.GetLength() == freqCv.GetLength());

	if (model != m_model) {
		m_model = model;
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
		switch (nPoles) {
		case 4:
			transFilt.transistorLadder<4>(freqCv.Get(), res, inBuf, outBuf, nSamp);
			break;
		case 2:
			transFilt.transistorLadder<2>(freqCv.Get(), res, inBuf, outBuf, nSamp);
			break;
		default:
			// TODO: log error
			transFilt.transistorLadder<4>(freqCv.Get(), res, inBuf, outBuf, nSamp);
			break;
		}
		break;

	case filterModel_diodeLadder:
		// Diode filter freqs are normalized so Nyquist = 1.0, so scale freqs accordingly
		diodeFilt.set_q(res);
		diodeFilt.set_feedback_hpf_cutoff(k_diodeResHpfCutoff_Hz / m_sampleRate * 2.0);

		for (size_t n = 0; n < nSamp; ++n) {
			float fc = freqCv[n];
			fc = fc * 2.0f;
			fc = Utils::Clip(fc, 0.001f, 0.999f);
			outBuf[n] = float(diodeFilt.tick(double(inBuf[n]), double(fc)));
		}

		break;

	case filterModel_ota:
		// TODO
		break;

	default:
		DEBUG_ASSERT_FAIL("Unknown filter model");
		break;
	}
}

void Filter::Process(Buffer& buf, sample_t freq, double res, filterModel_t model, uint8_t nPoles) {
	DEBUG_ASSERT(m_sampleRate > 0.0);

	if (model != m_model) {
		m_model = model;
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
		switch (nPoles) {
		case 4:
			transFilt.transistorLadder<4>(freq, res, inBuf, outBuf, nSamp);
			break;
		case 2:
			transFilt.transistorLadder<2>(freq, res, inBuf, outBuf, nSamp);
			break;
		default:
			// TODO: log error
			transFilt.transistorLadder<4>(freq, res, inBuf, outBuf, nSamp);
			break;
		}
		break;

	case filterModel_diodeLadder:
		// Diode filter freqs are normalized so Nyquist = 1.0, so scale freqs accordingly
		diodeFilt.set_q(res);
		diodeFilt.set_feedback_hpf_cutoff(k_diodeResHpfCutoff_Hz / m_sampleRate * 2.0);

		freq = Utils::Clip(2.0f*freq, 0.001f, 0.999f);

		for (size_t n = 0; n < nSamp; ++n) {
			outBuf[n] = float(diodeFilt.tick(double(inBuf[n]), freq));
		}

		break;

	case filterModel_ota:
		// TODO
		break;

	default:
		DEBUG_ASSERT_FAIL("Unknown filter model");
		break;
	}
}

} // namespace Engine