/*
  ==============================================================================

    OnePole.h
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

#ifndef ONEPOLE_H_INCLUDED
#define ONEPOLE_H_INCLUDED

#include "Utils/Types.h"

#include <vector>

namespace Utils
{

class OnePole
{
    // In all cases here, wc is normalized frequency (fc/fs) - usually between 0 and 0.5
    // Interface is float, but uses doubles internally
    
public:
    OnePole();
    OnePole(double wc);

    // Processing functions:
    
    // Buffer - in-place and not
    void ProcessLowpass  (Buffer const& inBuf /*in*/, Buffer& outBuf /*out*/);
    void ProcessHighpass (Buffer const& inBuf /*in*/, Buffer& outBuf /*out*/);
    void ProcessLowpass  (Buffer& /*inout*/);
    void ProcessHighpass (Buffer& /*inout*/);
    
    // Raw buffer - in-place and not
    void ProcessLowpass  (sample_t const* inBuf /*in*/, sample_t* outBuf /*out*/, size_t nSamp /*in*/);
    void ProcessHighpass (sample_t const* inBuf /*in*/, sample_t* outBuf /*out*/, size_t nSamp /*in*/);
    void ProcessLowpass  (sample_t* buf /*inout*/, uint32_t nSamp /*in*/);
    void ProcessHighpass (sample_t* buf /*inout*/, uint32_t nSamp /*in*/);
    
    // Single sample
    float ProcessLowpass  (float samp /*in*/);
    float ProcessHighpass (float samp /*in*/);
	double ProcessLowpass  (double samp /*in*/);
	double ProcessHighpass (double samp /*in*/);

    // Other public functions:
    
    void SetFreq(double wc);

	void Clear();
	void SetVal(sample_t val);

	// helper functions to set freq
	inline void SetFreq(double fc, double sampleRate) { SetFreq(fc*sampleRate); }

	inline void SetRiseTime(double time_samp) { SetFreq(1.0 / (2.0 * M_PI * time_samp)); }
	inline void SetRiseTime(double time_s, double sampleRate) { SetFreq(1.0 / (2.0 * M_PI * time_s * sampleRate));  }
    
protected:
    
    // Vectorized functions
    void  ProcessBufLowpass_ (sample_t const* inBuf, sample_t* outBuf, size_t nSamp);
    void  ProcessBufHighpass_(sample_t const* inBuf, sample_t* outBuf, size_t nSamp);
    void  ProcessBufLowpass_ (Buffer const& inBuf /*in*/, Buffer& outBuf /*out*/);
    void  ProcessBufHighpass_(Buffer const& inBuf /*in*/, Buffer& outBuf /*out*/);
    
    // Coefficient calculation
    void CalcCoeffs_(double wc);

    double z1; // Memory
    double a1; // FB Coeff
    double b0; // FF Coeff
};
   
} // namespace Engine


#endif  // ONEPOLE_H_INCLUDED
