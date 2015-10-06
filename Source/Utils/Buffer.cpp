/*
  ==============================================================================

    Buffer.cpp
    Created: 7 Sep 2015 10:21:20am
    Author:  Joel

  ==============================================================================
*/

#include "Buffer.h"

#include "Utils/ApproxEqual.h"

namespace Utils {

// Most member functions are inlined in Buffer.h

// ***** Constructors *****

// Unallocated constructor
Buffer::Buffer() :
	m_len(0),
	m_p(0),
	m_bOwnsBuf(false)
{}

// Uninitialized constructor
Buffer::Buffer(size_t len) :
	m_len(len),
	m_p(new sample_t[len]),
	m_bOwnsBuf(true)
{}

// Initialized constructor
Buffer::Buffer(sample_t val, size_t len) :
	m_len(len),
	m_p(new sample_t[len]),
	m_bOwnsBuf(true)
{
	if (val == 0.0f)
		Clear();
	else
		Set(val);
}

// Move constructor
Buffer::Buffer(Buffer && other) :
	m_len(other.m_len),
	m_p(other.m_p),
	m_bOwnsBuf(true)
{
	other.m_len = 0;
	other.m_p = 0;
	other.m_bOwnsBuf = false;
}

// Copy constructor
Buffer::Buffer(Buffer const& other) :
	m_len(other.GetLength()),
	m_p(new sample_t[m_len]),
	m_bOwnsBuf(true)
{
	juce::FloatVectorOperations::copy(m_p, other.GetConst(), m_len);
}

// Using preallocated block
Buffer::Buffer(sample_t* buf, size_t len) :
	m_len(len),
	m_p(buf),
	m_bOwnsBuf(false)
{}

// Destructor
Buffer::~Buffer()
{
	if (m_bOwnsBuf) delete[] m_p;
}


// ***** Private alloc functions *****

void Buffer::Dealloc_() {
	if (m_bOwnsBuf) delete[] m_p;
	m_p = 0;
	m_len = 0;
	m_bOwnsBuf = false;
}

// Always reallocates - usually want to check if (m_len == newLen) first
void Buffer::Realloc_(size_t newLen) {
	Dealloc_();
	m_len = newLen;
	m_p = new sample_t[m_len];
	m_bOwnsBuf = true;
}

// ***** Getters & Setters *****

void Buffer::Set(sample_t* buf, size_t len) {
	Dealloc_();
	m_p = buf;
	m_len = len;
	m_bOwnsBuf = false;
}

// same as operator=(Buffer&&)
void Buffer::MoveFrom(Buffer && other) {
	if (m_p == other.m_p) return;

	Dealloc_();
	m_len = other.m_len;
	m_p = other.m_p;

	m_bOwnsBuf = other.m_bOwnsBuf;
	other.m_bOwnsBuf = false;
}

// ***** Operators: (Approximate) equality *****

bool operator==(Buffer const& lhs, Buffer const& rhs)
	{ return Utils::ApproxEqual(lhs, rhs); }

bool operator!=(Buffer const& lhs, Buffer const& rhs)
	{ return !Utils::ApproxEqual(lhs, rhs); }

} // namespace Utils