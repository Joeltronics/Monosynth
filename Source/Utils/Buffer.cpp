/*
  ==============================================================================

    Buffer.cpp
    Created: 7 Sep 2015 10:21:20am
    Author:  Joel Geddert

  =============================================================================
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

#include "Buffer.h"

#include "Utils/ApproxEqual.h"

using namespace Utils;

// Most member functions are inlined in Buffer.h

// ***** Constructors *****

// Unallocated constructor
Buffer::Buffer() :
	m_allocLen(0),
	m_len(0),
	m_p(0),
	m_bOwnsBuf(false)
{}

// Uninitialized constructor
Buffer::Buffer(size_t len) :
	m_allocLen(len),
	m_len(len),
	m_p(new sample_t[len]),
	m_bOwnsBuf(true)
{}

// Uninitialized constructor
Buffer::Buffer(size_t len, size_t allocLen) :
	m_allocLen(allocLen),
	m_len(len),
	m_p(new sample_t[allocLen]),
	m_bOwnsBuf(true)
{
	DEBUG_ASSERT(len <= allocLen);
}

// Initialized constructor
Buffer::Buffer(sample_t val, size_t len) :
	m_allocLen(len),
	m_len(len),
	m_p(new sample_t[len]),
	m_bOwnsBuf(true)
{
	if (val == 0.0f)
		Clear();
	else
		Set(val);
}

// Initialized constructor
Buffer::Buffer(sample_t val, size_t len, size_t allocLen) :
	m_allocLen(allocLen),
	m_len(len),
	m_p(new sample_t[allocLen]),
	m_bOwnsBuf(true)
{
	DEBUG_ASSERT(len <= allocLen);
	if (val == 0.0f)
		Clear();
	else
		Set(val);
}

// Move constructor
Buffer::Buffer(Buffer && other) :
	m_allocLen(other.m_allocLen),
	m_len(other.m_len),
	m_p(other.m_p),
	m_bOwnsBuf(true)
{
	other.m_allocLen = 0;
	other.m_len = 0;
	other.m_p = 0;
	other.m_bOwnsBuf = false;
}

#if ALLOW_ALLOC

// Copy constructor
Buffer::Buffer(Buffer const& other) :
	m_len(other.GetLength()),
	m_allocLen(other.GetAllocLength()),
	m_p(new sample_t[m_allocLen]),
	m_bOwnsBuf(true)
{
	juce::FloatVectorOperations::copy(m_p, other.GetConst(), m_len);
}

// Copy with gain
Buffer::Buffer(Buffer const& other, sample_t gain) :
	m_len(other.GetLength()),
	m_allocLen(other.GetAllocLength()),
	m_p(new sample_t[m_allocLen]),
	m_bOwnsBuf(true)
{
	juce::FloatVectorOperations::copyWithMultiply(m_p, other.GetConst(), gain, m_len);
}

#endif

// Using preallocated block
Buffer::Buffer(sample_t* buf, size_t len) :
	m_len(len),
	m_allocLen(len),
	m_p(buf),
	m_bOwnsBuf(false)
{}

// Destructor
Buffer::~Buffer()
{
	if (m_bOwnsBuf) delete[] m_p;
}

// ***** Resizing & allocating functions *****

void Buffer::Resize(size_t newLen, bool bForceRealloc) {

	if (bForceRealloc || newLen > m_allocLen) {
		Dealloc_();
		Alloc_(newLen);
	}

	m_len = newLen;
}

void Buffer::Dealloc_() {
	if (m_bOwnsBuf) delete[] m_p;
	m_p = 0;
	m_len = 0;
	m_allocLen = 0;
	m_bOwnsBuf = false;
}

void Buffer::Alloc_(size_t newAllocLen) {
	m_allocLen = newAllocLen;
	m_p = new sample_t[m_allocLen];
	m_bOwnsBuf = true;
}

// ***** Getters & Setters *****

void Buffer::Set(sample_t* buf, size_t len) {
	Dealloc_();
	m_p = buf;
	m_len = len;
	m_allocLen = len;
	m_bOwnsBuf = false;
}

// same as operator=(Buffer&&)
void Buffer::MoveFrom(Buffer && other) {
	if (m_p == other.m_p) return;

	Dealloc_();
	
	m_p = other.m_p;

	m_bOwnsBuf = other.m_bOwnsBuf;
	other.m_bOwnsBuf = false;
	
	m_allocLen = other.m_allocLen;
	other.m_allocLen = 0;

	m_len = other.m_len;
	other.m_len = 0;
}

// ***** Operators: (Approximate) equality *****

bool Utils::operator==(Buffer const& lhs, Buffer const& rhs)
	{ return Utils::ApproxEqual(lhs, rhs); }

bool Utils::operator!=(Buffer const& lhs, Buffer const& rhs)
	{ return !Utils::ApproxEqual(lhs, rhs); }
