/*
  ==============================================================================

    OnePole.cpp
    Created: 7 Jul 2015 8:40:41am
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

#include "OnePole.h"

#include "Debug.h"
#include "Utils/Types.h"
#include "DspUtils.h"
#include "ApproxEqual.h"

#include <cmath>
//#include <math.h>

namespace Utils
{

// ***** Constructors *****

OnePole::OnePole() :
	a1(0.0),
	b0(1.0)
{
	Clear();
}
    
OnePole::OnePole(double wc) {
	Clear();
	CalcCoeffs_(wc);
}

// ***** Process *****

void OnePole::ProcessLowpass(Buffer& buf /*inout*/) {
	ProcessBufLowpass_(buf, buf);
}

void OnePole::ProcessHighpass(Buffer& buf /*inout*/) {
	ProcessBufHighpass_(buf, buf);
}

void OnePole::ProcessLowpass(Buffer const& inBuf, Buffer& outBuf) {
	DEBUG_ASSERT(inBuf.GetLength() == outBuf.GetLength());
	ProcessBufLowpass_(inBuf, outBuf);
}

void OnePole::ProcessHighpass(Buffer const& inBuf, Buffer& outBuf) {
	DEBUG_ASSERT(inBuf.GetLength() == outBuf.GetLength());
	ProcessBufHighpass_(inBuf, outBuf);
}

void OnePole::ProcessLowpass(sample_t* buf /*inout*/, uint32_t nSamp) {
	ProcessBufLowpass_(buf, buf, nSamp);
}
    
void OnePole::ProcessHighpass(sample_t* buf /*inout*/, uint32_t nSamp) {
	ProcessBufHighpass_(buf, buf, nSamp);
}

void OnePole::ProcessLowpass(sample_t const* inBuf, sample_t* outBuf /*out*/, size_t nSamp) {
	ProcessBufLowpass_(inBuf, outBuf, nSamp);
}

void OnePole::ProcessHighpass(sample_t const* inBuf, sample_t* outBuf /*out*/, size_t nSamp) {
	ProcessBufHighpass_(inBuf, outBuf, nSamp);
}
    
float OnePole::ProcessLowpass(float samp) {
	z1 = b0*double(samp) + a1*z1;
	return float(z1);
}

float OnePole::ProcessHighpass(float samp) {
	z1 = b0*double(samp) + a1*z1;
	return samp - float(z1);
}

double OnePole::ProcessLowpass(double samp) {
	z1 = b0*samp + a1*z1;
	return z1;
}

double OnePole::ProcessHighpass(double samp) {
	z1 = b0*samp + a1*z1;
	return samp - z1;
}

void OnePole::ProcessLowpass(BufferOrVal& buf /*inout*/, sample_t approxEqualThresh) {
	
	if (buf.IsVal()) {

		sample_t val = buf.GetVal();

		// If filter output memory (z1) is very close to input value, then don't need to process
		bool bSkipProcessing = ApproxEqual(val, sample_t(z1), approxEqualThresh);

		if (bSkipProcessing) {
			z1 = double(val);
			return;
		}

		buf.ConvertValToBuf();
	}
	
	ProcessBufLowpass_(buf.GetBuf(), buf.GetBuf());
}

void OnePole::ProcessHighpass(BufferOrVal& buf /*inout*/, sample_t approxEqualThresh) {

	if (buf.IsVal()) {

		sample_t val = buf.GetVal();

		// If filter output memory (z1) is very close to input value, then don't need to process
		bool bSkipProcessing = ApproxEqual(val, sample_t(z1), approxEqualThresh);

		if (bSkipProcessing) {
			z1 = double(val);
			return;
		}

		buf.ConvertValToBuf();
	}

	ProcessBufHighpass_(buf.GetBuf(), buf.GetBuf());
}

// ***** Private processing functions *****
    
// TODO: vectorize these!
/*
Could easily vectorize b0*samp calc - but because we're multiplying a float by
a double, can't easily do this vectorized
 
There are also more complicated ways to fully fectorize IIR filters:
http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.217.5808&rep=rep1&type=pdf
http://reanimator-web.appspot.com/articles/simdiir
http://dsp.stackexchange.com/questions/1075/how-can-i-vectorize-the-computations-for-a-first-order-recursive-filter
*/

void OnePole::ProcessBufLowpass_(sample_t const* inBuf, sample_t* outBuf, size_t nSamp) {
	for (uint32_t n=0; n < nSamp; n++) {
		z1 = b0*double(inBuf[n]) + a1*z1;
		outBuf[n] = float(z1);
	}
}

void OnePole::ProcessBufHighpass_(sample_t const* inBuf, sample_t* outBuf, size_t nSamp) {
	for (uint32_t n = 0; n < nSamp; n++) {
		z1 = b0*double(inBuf[n]) + a1*z1;
		outBuf[n] = float(double(inBuf[n] - z1));
	}
}

void OnePole::ProcessBufLowpass_(Buffer const& inBuf, Buffer& outBuf)
	{ ProcessBufLowpass_(inBuf.GetConst(), outBuf.Get(), inBuf.GetLength()); }

void OnePole::ProcessBufHighpass_(Buffer const& inBuf /*in*/, Buffer& outBuf /*out*/)
	{ ProcessBufHighpass_(inBuf.GetConst(), outBuf.Get(), inBuf.GetLength()); }
    
// ***** Other public functions *****

void OnePole::SetFreq(double wc) { CalcCoeffs_(wc); }

void OnePole::Clear() { z1 = 0.0; }

void OnePole::SetVal(sample_t val) { z1 = val; }

// ***** Other Private functions *****

void OnePole::CalcCoeffs_(double wc) {
	a1 = exp(-2.0*M_PI * wc);
	b0 = 1.0 - a1;
}

} // namespace Utils