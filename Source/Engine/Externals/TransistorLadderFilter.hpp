//// LICENSE TERMS: Copyright 2012 Teemu Voipio
// 
// You can use this however you like for pretty much any purpose,
// as long as you don't claim you wrote it. There is no warranty.
//
// Distribution of substantial portions of this code in source form
// must include this copyright notice and list of conditions.
//

// jgeddert mods: wrapped in c++ class, added include guards, added includes
#ifndef __TRANSISTOR_LADDER_FILTER_HPP__
#define __TRANSISTOR_LADDER_FILTER_HPP__

#include <cmath>
#include <algorithm>

class TransistorLadderFilter
{
private:
	// input delay and state for member variables
	double zi;
	double s[4];

public:
	
	TransistorLadderFilter() :
		zi(0.0),
		s{0.0, 0.0, 0.0, 0.0}
	{}
	
	~TransistorLadderFilter() {}

	// jgedderd mod: added this function
	void reset()
	{
		zi = 0.0;
		std::fill(s, s + 4, 0.0);
	}

	// tanh(x)/x approximation, flatline at very high inputs
	// so might not be safe for very large feedback gains
	// [limit is 1/15 so very large means ~15 or +23dB]
	static double tanhXdX(double x)
	{
		double a = x*x;
		// IIRC I got this as Pade-approx for tanh(sqrt(x))/sqrt(x) 
		return ((a + 105)*a + 945) / ((15*a + 420)*a + 945);
	}

	// cutoff as normalized frequency (eg 0.5 = Nyquist)
	// resonance from 0 to 1, self-oscillates at settings over 0.9
	// jgeddert mod: converted to use float* inputs
	// jgeddert mod: added nPoles
	// npoles is templated to help ensure compiler optimizes to be branch-free
	template <size_t nPoles>
	void transistorLadder(
		float* cutoff, double resonance,
		float const* in, float * out, size_t nsamples)
	{
		// tuning and feedback
		double r = (40.0/9.0) * resonance;

		juce::FloatVectorOperations::clip(cutoff, cutoff, 0.0001f, 0.4999f, nsamples);
		
#if 0
		// Full accuracy
		for (size_t n = 0; n < nsamples; ++n) {
			cutoff[n] = tan(float(M_PI) * cutoff[n]);
		}
#else
		// Small-angle approximation (okay because we're oversampling)
		juce::FloatVectorOperations::multiply(cutoff, float(M_PI), nsamples);
#endif
		

		for(size_t n = 0; n < nsamples; ++n)
		{
			double f = double(cutoff[n]);
			double inn = double(in[n]);
			
			// input with half delay, for non-linearities
			double ih = 0.5 * (inn + zi); zi = inn;

			// evaluate the non-linear gains
			double t0 = tanhXdX(ih - r * s[3]);
			double t1 = tanhXdX(s[0]);
			double t2 = tanhXdX(s[1]);
			double t3 = tanhXdX(s[2]);
			double t4 = tanhXdX(s[3]);

			// g# the denominators for solutions of individual stages
			double g0 = 1 / (1 + f*t1), g1 = 1 / (1 + f*t2);
			double g2 = 1 / (1 + f*t3), g3 = 1 / (1 + f*t4);
			
			// f# are just factored out of the feedback solution
			double f3 = f*t3*g3, f2 = f*t2*g2*f3, f1 = f*t1*g1*f2, f0 = f*t0*g0*f1;

			// solve feedback 
			double y3 = (g3*s[3] + f3*g2*s[2] + f2*g1*s[1] + f1*g0*s[0] + f0*inn) / (1 + r*f0);

			// then solve the remaining outputs (with the non-linear gains here)
			double xx = t0*(inn - r*y3);
			double y0 = t1*g0*(s[0] + f*xx);
			double y1 = t2*g1*(s[1] + f*y0);
			double y2 = t3*g2*(s[2] + f*y1);

			// update state
			s[0] += 2*f * (xx - y0);
			s[1] += 2*f * (y0 - y1);
			s[2] += 2*f * (y1 - y2);
			s[3] += 2*f * (y2 - t4*y3);

			static_assert(nPoles <= 4, "LadderFilter has max 4 poles!");

			switch (nPoles) {
			case 4:
				out[n] = float(y3);
				break;
			case 3:
				out[n] = float(y2);
				break;
			case 2:
				out[n] = float(y1);
				break;
			case 1:
				out[n] = float(y0);
				break;
			case 0:
				out[n] = float(xx);
				break;
			}
		}
	}

	// cutoff as normalized frequency (eg 0.5 = Nyquist)
	// resonance from 0 to 1, self-oscillates at settings over 0.9
	// jgeddert mod: converted to use float* inputs
	// jgeddert mod: added nPoles
	// npoles is templated to help ensure compiler optimizes to be branch-free
	template <size_t nPoles>
	void transistorLadder(
		float cutoff, double resonance,
		float const* in, float * out, size_t nsamples)
	{
		// tuning and feedback
		double r = (40.0 / 9.0) * resonance;

		cutoff = Utils::Clip(cutoff, 0.0001f, 0.4999f);

#if 0
		// Full accuracy
		cutoff = tan(float(M_PI) * cutoff);
#else
		// Small-angle approximation (okay because we're oversampling)
		cutoff *= float(M_PI);
#endif

		double f = double(cutoff);

		for (size_t n = 0; n < nsamples; ++n)
		{
			double inn = double(in[n]);

			// input with half delay, for non-linearities
			double ih = 0.5 * (inn + zi); zi = inn;

			// evaluate the non-linear gains
			double t0 = tanhXdX(ih - r * s[3]);
			double t1 = tanhXdX(s[0]);
			double t2 = tanhXdX(s[1]);
			double t3 = tanhXdX(s[2]);
			double t4 = tanhXdX(s[3]);

			// g# the denominators for solutions of individual stages
			double g0 = 1 / (1 + f*t1), g1 = 1 / (1 + f*t2);
			double g2 = 1 / (1 + f*t3), g3 = 1 / (1 + f*t4);

			// f# are just factored out of the feedback solution
			double f3 = f*t3*g3, f2 = f*t2*g2*f3, f1 = f*t1*g1*f2, f0 = f*t0*g0*f1;

			// solve feedback 
			double y3 = (g3*s[3] + f3*g2*s[2] + f2*g1*s[1] + f1*g0*s[0] + f0*inn) / (1 + r*f0);

			// then solve the remaining outputs (with the non-linear gains here)
			double xx = t0*(inn - r*y3);
			double y0 = t1*g0*(s[0] + f*xx);
			double y1 = t2*g1*(s[1] + f*y0);
			double y2 = t3*g2*(s[2] + f*y1);

			// update state
			s[0] += 2 * f * (xx - y0);
			s[1] += 2 * f * (y0 - y1);
			s[2] += 2 * f * (y1 - y2);
			s[3] += 2 * f * (y2 - t4*y3);

			static_assert(nPoles <= 4, "LadderFilter has max 4 poles!");

			switch (nPoles) {
			case 4:
				out[n] = float(y3);
				break;
			case 3:
				out[n] = float(y2);
				break;
			case 2:
				out[n] = float(y1);
				break;
			case 1:
				out[n] = float(y0);
				break;
			case 0:
				out[n] = float(xx);
				break;
			}
		}
	}

}; // class TransistorLadderFilter

#endif // __TRANSISTOR_LADDER_FILTER_HPP__
