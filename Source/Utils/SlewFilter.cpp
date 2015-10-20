/*
  ==============================================================================

    SlewFilter.cpp
    Created: 25 Jul 2015 5:13:52pm
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

#include "SlewFilter.h"

#include "Debug.h"
#include "DspUtils.h"

namespace Utils
{

namespace Detail
{
    static inline float Process(float samp, float prevSamp, float rate)
    {
        float delta = samp - prevSamp;
        delta = Utils::Clip(delta, rate);
        return prevSamp + delta;
    }
}
 
// ***** Constructors *****
    
SlewFilter::SlewFilter() :
    m_rate(1.0f)
{
    Clear();
}
    
SlewFilter::SlewFilter(float rate) :
    m_rate(rate)
{
    Clear();
}

// ***** Process *****

// Buffer
void SlewFilter::Process(Buffer const& inBuf /*in*/, Buffer& outBuf /*out*/) {
    DEBUG_ASSERT(inBuf.GetLength() == outBuf.GetLength());
	Process(inBuf.GetConst(), outBuf.Get(), inBuf.GetLength());
}

// Buffer - in-place
void SlewFilter::Process(Buffer& buf /*inout*/)
	{ Process(buf.Get(), buf.GetLength()); }

// Raw buffer
void SlewFilter::Process(float const* inBuf /*in*/, float* outBuf /*out*/, uint32_t nSamp /*in*/) {
    for (uint32_t n=0; n < nSamp; n++) {
        z1 = Detail::Process(inBuf[n], z1, m_rate);
        outBuf[n] = z1;
    }
}

// Raw buffer - in-place
void SlewFilter::Process(float* buf /*inout*/, uint32_t nSamp /*in*/)
	{ Process(buf, buf, nSamp); }

// Single sample
float SlewFilter::Process(float samp /*in*/) {
    float const out = Detail::Process(samp, z1, m_rate);
    z1 = out;
    return out;
}

// ***** Other public functions *****

void SlewFilter::SetRate(float rate)
	{ m_rate = rate; }

void SlewFilter::Clear()
	{ z1 = 0.0f; }
    
} // namespace Engine