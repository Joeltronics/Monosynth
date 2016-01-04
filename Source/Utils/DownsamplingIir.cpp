/*
  ==============================================================================

    DownsamplingIir.cpp
    Created: 3 Jan 2016 2:49:05pm
    Author:  Joel

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

#include "Utils/Resampling.h"
#include "Utils/Buffer.h"

#include "Debug.h"

#include "JuceHeader.h"

using namespace Utils;

// ***** IIR Downsamplers *****

/*
TODO:
there are a bunch of ways this could be modified that *might* lead to
performance improvements but would need to be tested

1. Cascaded biquads vs single high-order filter:

Generally, cascaded biquad is considered better. I think this is because
of numerical stability, but there could be other reasons. However, try a
single high-order filter. Because we're using it for downsampling, we only
need every 2nd or every 4th output value. If we use one high-order filter,
then we can just not calculate the output values we don't need. With
cascaded biquads, we have to calculate every single output value of every
filter except for the very last one, because subsequent filters need the
output values

(The problem with high order filters is numerical stability - is there some
way to test?)

2. Swap loop orders so iterating through filters is the outermost loop:

This is incompatible with #1, and we'd have to calculate every single output
value. Also it would require allocating a buffer for temporary values.
However, I suspect it would gain other performance improvements. I'd have
to test it to be sure.
*/

static void ProcessIirDownsampHighOrder(
	Buffer& outBuf,
	sample_t* w,
	Buffer const& inBuf,
	size_t const nResamp,
	sample_t const* a,
	sample_t const* b,
	size_t const order)
{
	DEBUG_ASSERT(inBuf.GetLength() == outBuf.GetLength() * nResamp);
	sample_t const* rp = inBuf.GetConst();
	sample_t* wp = outBuf.Get();
	juce::FloatVectorOperations::enableFlushToZeroMode(true);

	size_t nInput = 0;
	for (size_t nOutput = 0; nOutput < outBuf.GetLength(); ++nOutput) {

		sample_t y;

		for (size_t m = 0; m < nResamp; ++m) { // iterate nResamp samples

			sample_t x = rp[nInput++];

			// w[n] =      x[n] - a[1]*w[n-1] - a[2]*w[n-2] - ...
			// y[n] = b[0]*w[n] + b[1]*w[n-1] + b[2]*w[n-2] + ...

			// TODO: Can move calculation of y outside loop, this will save 1/2 or 3/4 of y computation
#if 1
			// Good version of code below
			sample_t w0 = x;
			for (size_t r = 0; r < order; ++r) {
				w0 -= a[r+1] * w[r];
			}

			y = b[0]*w0;
			for (size_t r = 0; r < order; ++r) {
				y += b[r+1]*w[r];
			}
#else
			// Draft code (fixed above)
			// This code is bad, and yes I feel bad
			sample_t w0;
			switch (order) {
			case 4:
				w0 =      x - a[1]*w[0] - a[2]*w[1] - a[3]*w[2] - a[4]*w[3];
				y = b[0]*w0 + b[1]*w[0] + b[2]*w[1] + b[3]*w[2] + b[4]*w[3];
				break;
			case 6:
				w0 =      x - a[1]*w[0] - a[2]*w[1] - a[3]*w[2] - a[4]*w[3] - a[5]*w[4] - a[6]*w[5];
				y = b[0]*w0 + b[1]*w[0] + b[2]*w[1] + b[3]*w[2] + b[4]*w[3] + b[5]*w[4] + b[6]*w[5];
				break;
			case 8:
				w0 =      x - a[1]*w[0] - a[2]*w[1] - a[3]*w[2] - a[4]*w[3] - a[5]*w[4] - a[6]*w[5] - a[7]*w[6] - a[8]*w[7];
				y = b[0]*w0 + b[1]*w[0] + b[2]*w[1] + b[3]*w[2] + b[4]*w[3] + b[5]*w[4] + b[6]*w[5] + b[7]*w[6] + b[8]*w[7];
				break;
			case 10:
				w0 =      x - a[1]*w[0] - a[2]*w[1] - a[3]*w[2] - a[4]*w[3] - a[5]*w[4] - a[6]*w[5] - a[7]*w[6] - a[8]*w[7] - a[9]*w[8] - a[10]*w[9];
				y = b[0]*w0 + b[1]*w[0] + b[2]*w[1] + b[3]*w[2] + b[4]*w[3] + b[5]*w[4] + b[6]*w[5] + b[7]*w[6] + b[8]*w[7] + b[9]*w[8] + b[10]*w[9];
				break;
			default:
				DEBUG_ASSERT_FAIL("Filter order not implemented");
			}
#endif

			for (size_t r = (order-1); r > 0; --r) {
				w[r] = w[r-1];
			}
			w[0] = w0;
		}

		wp[nOutput] = y;
	}
}

static void ProcessIirDownsampCascaded(
	Buffer& outBuf,
	sample_t* z,
	Buffer const& inBuf,
	size_t const nResamp,
	sample_t const biquadCoeffs[][6], // 2D array [nBiquad][6]
	size_t const nBiquad)
{
	DEBUG_ASSERT(inBuf.GetLength() == outBuf.GetLength() * nResamp);
	sample_t const* rp = inBuf.GetConst();
	sample_t* wp = outBuf.Get();
	juce::FloatVectorOperations::enableFlushToZeroMode(true);

	size_t nInput = 0;
	for (size_t nOutput = 0; nOutput < outBuf.GetLength(); ++nOutput) {

		sample_t y;

		for (size_t m = 0; m < nResamp; ++m) { // iterate nResamp samples

			sample_t x = rp[nInput++];

			for (size_t nFilt = 0; nFilt < nBiquad; ++nFilt) {

				// Set up IIR filter - get coeffs and sample
				// (These references are just to make code readable - compiler will optimize out)

				// Feed-forward
				sample_t const& b0 = biquadCoeffs[nFilt][0];
				sample_t const& b1 = biquadCoeffs[nFilt][1];
				sample_t const& b2 = biquadCoeffs[nFilt][2];

				// Feedback
				// (a0 = 1)
				sample_t const& a1 = biquadCoeffs[nFilt][4];
				sample_t const& a2 = biquadCoeffs[nFilt][5];

				sample_t w;
				sample_t& w1 = z[2*nFilt];
				sample_t& w2 = z[2*nFilt + 1];

				// w[n] =      x[n] - a[1]*w[n-1] - a[2]*w[n-2]
				// y[n] = b[0]*w[n] + b[1]*w[n-1] + b[2]*w[n-2]

				w =    x - a1*w1 - a2*w2;
				y = b0*w + b1*w1 + b2*w2;

				w2 = w1;
				w1 = w;

				// Input to next filter is output from previous
				x = y;
			}
		}

		wp[nOutput] = y;
	}
}

void IirDownsampler_176_44::Process(Buffer& outBuf, Buffer const& inBuf) {
	ProcessIirDownsampCascaded(outBuf, z, inBuf, nResamp, IirCoeffs::biquad_176_44, nBiquad);
	//ProcessIirDownsampHighOrder(outBuf, z, inBuf, nResamp, IirCoeffs::a_176_44, IirCoeffs::b_176_44, order);
}

void IirDownsampler_176_88::Process(Buffer& outBuf, Buffer const& inBuf) {
	ProcessIirDownsampCascaded(outBuf, z, inBuf, nResamp, IirCoeffs::biquad_176_88, nBiquad);
	//ProcessIirDownsampHighOrder(outBuf, z, inBuf, nResamp, IirCoeffs::a_176_88, IirCoeffs::b_176_88, order);
}

void IirDownsampler_192_48::Process(Buffer& outBuf, Buffer const& inBuf) {
	ProcessIirDownsampCascaded(outBuf, z, inBuf, nResamp, IirCoeffs::biquad_192_48, nBiquad);
	//ProcessIirDownsampHighOrder(outBuf, z, inBuf, nResamp, IirCoeffs::a_192_48, IirCoeffs::b_192_48, order);
}

void IirDownsampler_192_96::Process(Buffer& outBuf, Buffer const& inBuf) {
	ProcessIirDownsampCascaded(outBuf, z, inBuf, nResamp, IirCoeffs::biquad_192_96, nBiquad);
	//ProcessIirDownsampHighOrder(outBuf, z, inBuf, nResamp, IirCoeffs::a_192_96, IirCoeffs::b_192_96, order);
}

#define DEF_IIR_FUNCS(CLASSNAME) \
void CLASSNAME::Clear() { \
	juce::FloatVectorOperations::clear(z, order); \
} \
CLASSNAME::CLASSNAME() { \
	static_assert(order == 2*nBiquad, ""); \
	Clear(); \
}

DEF_IIR_FUNCS(IirDownsampler_176_44);
DEF_IIR_FUNCS(IirDownsampler_176_88);
DEF_IIR_FUNCS(IirDownsampler_192_48);
DEF_IIR_FUNCS(IirDownsampler_192_96);

