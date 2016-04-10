/*
  ==============================================================================

    Buffer.h
    Created: 6 Sep 2015 1:32:27pm
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

#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#include "Utils/Types.h"

// We must avoid allocating in the audio thread in order to guarantee real-time
// That makes some operations here unsafe to use in the audio thread.
// ALLOW_ALLOC sets whether these operations are enabled or not
// For now, set to 1 - but will eventually want to remove all cases that use these functions
#define ALLOW_ALLOC 1

#define REQUIRE_EXPLICIT_RESIZE 0

namespace Utils {

class Buffer {
	// Most member functions inlined below
public:

	// ***** Constructors *****
	Buffer(); // Unallocated
	Buffer(size_t len); // Allocated, uninitialized
	Buffer(size_t len, size_t allocLen); // Allocated, uninitialized
	Buffer(sample_t val, size_t len); // Allocate and initialize to value
	Buffer(sample_t val, size_t len, size_t allocLen); // Allocate and initialize to value
	Buffer(Buffer && other); // Move
	Buffer(sample_t* buf, size_t len); // Using preallocated block
#if ALLOW_ALLOC
	Buffer(Buffer const& other); // Copy
	Buffer(Buffer const& other, sample_t gain); // Copy with multiply
#endif

	~Buffer();

	// ***** Getters & setters *****

	void Clear(); // Sets all to zero
	void Set(sample_t val);
	void Set(sample_t* buf, size_t len); // doesn't take ownership
	void MoveFrom(Buffer && other); // Takes ownership; same as operator=

#if !(REQUIRE_EXPLICIT_RESIZE)
	void Clear(size_t len);
	void Set(sample_t val, size_t len);
	void CopyFrom(Buffer const& other); // same as operator=
	void CopyFrom(sample_t* buf, size_t len);
#endif

	sample_t* Get();
	sample_t const* GetConst() const;
	size_t GetLength() const;
	size_t GetAllocLength() const;

	// Will cause realloc if newLen > allocLen, or if bForceRealloc
	void Resize(size_t newLen, bool bForceRealloc=false);

	// ***** Operators *****

	void AddWithMultiply(Buffer const& other, sample_t multiplier);

	// move & copy
	Buffer& operator=(Buffer && other); // same as MoveFrom()
	Buffer& operator=(Buffer const& other); // same as CopyFrom()

	// dereference
	sample_t operator[](size_t idx); // get sample
	sample_t* operator*(); // get pointer to sample buffer

	// (approximate) equality - uses Utils::ApproxEqual() internally
	friend bool operator==(Buffer const& lhs, Buffer const& rhs);
	friend bool operator!=(Buffer const& lhs, Buffer const& rhs);

	// math in place
	Buffer& operator+=(Buffer const& other);
	Buffer& operator+=(sample_t val);
	Buffer& operator-=(Buffer const& other);
	Buffer& operator-=(sample_t val);
	Buffer& operator*=(Buffer const& other);
	Buffer& operator*=(sample_t val);
	Buffer& operator/=(Buffer const& other); /// warning: slower, because there's no juce::FloatVectorOperations::divide
	Buffer& operator/=(sample_t val); /// not slower - calculates 1/val and then multiplies

	// math out of place
#if ALLOW_ALLOC
	Buffer operator-();
	friend Buffer operator+(Buffer const& lhs, Buffer const& rhs);
	friend Buffer operator+(Buffer const& lhs, sample_t rhs);
	friend Buffer operator-(Buffer const& lhs, Buffer const& rhs);
	friend Buffer operator-(Buffer const& lhs, sample_t rhs);
	friend Buffer operator*(Buffer const& lhs, Buffer const& rhs);
	friend Buffer operator*(Buffer const& lhs, sample_t rhs);
	friend Buffer operator/(Buffer const& lhs, Buffer const& rhs); /// warning: slower (see above)
	friend Buffer operator/(Buffer const& lhs, sample_t rhs);
#endif

private:
	void Dealloc_();
	void Alloc_(size_t newAllocLen);

	/*
	There may be some cases we want to over-allocate, either to stay byte-aligned or
	in order to avoid future reallocs in the audio thread. Se we keep track of both
	how many samples are allocated as well as how many we've defined as actually using
	*/
	size_t m_allocLen; /// how many samples are allocated
	size_t m_len; /// how many of these samples are actually in use

	sample_t* m_p;
	bool m_bOwnsBuf; /// whether or not to delete on destruction/reallocation
};

// ***** Getters & setters *****

inline sample_t* Buffer::Get() {
	return m_p;
}

inline sample_t const* Buffer::GetConst() const {
	return m_p;
}

inline void Buffer::Clear() {
	juce::FloatVectorOperations::clear(m_p, m_len);
}

inline void Buffer::Set(sample_t val) {
	juce::FloatVectorOperations::fill(m_p, val, m_len);
}

#if !(REQUIRE_EXPLICIT_RESIZE)

inline void Buffer::Clear(size_t len) {
	if (m_len != len) Resize(len);
	juce::FloatVectorOperations::clear(m_p, m_len);
}

inline void Buffer::Set(sample_t val, size_t len) {
	if (m_len != len) Resize(len);
	juce::FloatVectorOperations::fill(m_p, val, len);
}

inline void Buffer::CopyFrom(sample_t* buf, size_t len) {
	if (m_len != len) Resize(len);
	juce::FloatVectorOperations::copy(m_p, buf, m_len);
}

// same as operator=(Buffer)
inline void Buffer::CopyFrom(Buffer const& other) {
	if (m_len != other.m_len) Resize(other.m_len);
	juce::FloatVectorOperations::copy(m_p, other.GetConst(), m_len);
}

#endif // !REQUIRE_EXPLICIT_RESIZE

inline size_t Buffer::GetLength() const {
	return m_len;
}

inline size_t Buffer::GetAllocLength() const {
	return m_allocLen;
}

// ***** Operators: Move & Copy *****

inline Buffer& Buffer::operator=(Buffer && other) {
	MoveFrom(std::forward<Buffer>(other));
	return *this;
}

inline Buffer& Buffer::operator=(Buffer const& other) {
	CopyFrom(other);
	return *this;
}

// ***** Operators: Dereference *****

inline sample_t Buffer::operator[](size_t idx) {
	DEBUG_ASSERT(idx < m_len);
	return m_p[idx];
}

inline sample_t* Buffer::operator*() {
	return m_p;
}

// ***** Operators: In-place math *****

inline void Buffer::AddWithMultiply(Buffer const& other, sample_t multiplier) {
	DEBUG_ASSERT(m_len == other.m_len);
	juce::FloatVectorOperations::addWithMultiply(m_p, other.GetConst(), multiplier, m_len);
}

inline Buffer& Buffer::operator+=(Buffer const& other) {
	DEBUG_ASSERT(m_len == other.m_len);
	juce::FloatVectorOperations::add(m_p, other.GetConst(), m_len);
	return *this;
}

inline Buffer& Buffer::operator+=(sample_t val) {
	juce::FloatVectorOperations::add(m_p, val, m_len);
	return *this;
}

inline Buffer& Buffer::operator-=(Buffer const& other) {
	DEBUG_ASSERT(m_len == other.m_len);
	juce::FloatVectorOperations::subtract(m_p, other.GetConst(), m_len);
	return *this;
}

inline Buffer& Buffer::operator-=(sample_t val) {
	juce::FloatVectorOperations::add(m_p, -val, m_len);
	return *this;
}

inline Buffer& Buffer::operator*=(Buffer const& other) {
	DEBUG_ASSERT(m_len == other.m_len);
	juce::FloatVectorOperations::multiply(m_p, other.GetConst(), m_len);
	return *this;
}

inline Buffer& Buffer::operator*=(sample_t val) {
	juce::FloatVectorOperations::multiply(m_p, val, m_len);
	return *this;
}

inline Buffer& Buffer::operator/=(Buffer const& other) {
	DEBUG_ASSERT(m_len == other.m_len);
	for (size_t n = 0; n < m_len; ++n)
		m_p[n] /= other.m_p[n];
	return *this;
}

inline Buffer& Buffer::operator/=(sample_t val) {
	juce::FloatVectorOperations::multiply(m_p, sample_t(1.0) / val, m_len);
	return *this;
}

// ***** Operators: out-of-place math *****

#if ALLOW_ALLOC

inline Buffer Buffer::operator-() {
	Buffer newBuf(m_len);
	juce::FloatVectorOperations::negate(newBuf.m_p, m_p, m_len);
	return newBuf;
}

inline Buffer operator+(Buffer const& lhs, Buffer const& rhs) {
	DEBUG_ASSERT(lhs.m_len == rhs.m_len);
	Buffer newBuf(lhs.m_len);
	juce::FloatVectorOperations::add(newBuf.m_p, lhs.m_p, rhs.m_p, lhs.m_len);
	return newBuf;
}
inline Buffer operator+(Buffer const& lhs, sample_t rhs) {
	Buffer newBuf(lhs.m_len);
	juce::FloatVectorOperations::add(newBuf.m_p, lhs.m_p, rhs, lhs.m_len);
	return newBuf;
}
inline Buffer operator-(Buffer const& lhs, Buffer const& rhs) {
	DEBUG_ASSERT(lhs.m_len == rhs.m_len);
	Buffer newBuf(lhs.m_len);
	juce::FloatVectorOperations::subtract(newBuf.m_p, lhs.m_p, rhs.m_p, lhs.m_len);
	return newBuf;
}
inline Buffer operator-(Buffer const& lhs, sample_t rhs) {
	Buffer newBuf(lhs.m_len);
	juce::FloatVectorOperations::add(newBuf.m_p, lhs.m_p, -rhs, lhs.m_len);
	return newBuf;
}
inline Buffer operator*(Buffer const& lhs, Buffer const& rhs) {
	DEBUG_ASSERT(lhs.m_len == rhs.m_len);
	Buffer newBuf(lhs.m_len);
	juce::FloatVectorOperations::multiply(newBuf.m_p, lhs.m_p, rhs.m_p, lhs.m_len);
	return newBuf;
}
inline Buffer operator*(Buffer const& lhs, sample_t rhs) {
	Buffer newBuf(lhs.m_len);
	juce::FloatVectorOperations::copyWithMultiply(newBuf.m_p, lhs.m_p, rhs, lhs.m_len);
	return newBuf;
}
inline Buffer operator/(Buffer const& lhs, Buffer const& rhs) {
	DEBUG_ASSERT(lhs.m_len == rhs.m_len);
	Buffer newBuf(lhs.m_len);
	for (size_t n = 0; n < lhs.m_len; ++n)
		newBuf.m_p[n] = lhs.m_p[n] / rhs.m_p[n];
	return newBuf;
}
inline Buffer operator/(Buffer const& lhs, sample_t rhs) {
	Buffer newBuf(lhs.m_len);
	juce::FloatVectorOperations::copyWithMultiply(newBuf.m_p, lhs.m_p, sample_t(1.0) / rhs, lhs.m_len);
	return newBuf;
}

#endif

} // namespace Utils

#endif  // BUFFER_H_INCLUDED
