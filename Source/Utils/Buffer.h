/*
  ==============================================================================

    Buffer.h
    Created: 6 Sep 2015 1:32:27pm
    Author:  Joel

  ==============================================================================
*/

#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#include "Utils/Types.h"

namespace Utils {

class Buffer {
	// Most member functions inlined below
public:

	// ***** Constructors *****
	Buffer(); // Unallocated
	Buffer(size_t len); // Allocated, uninitialized
	Buffer(sample_t val, size_t len); // Allocate and initialize to value
	Buffer(Buffer && other); // Move
	Buffer(Buffer const& other); // Copy
	Buffer(sample_t* buf, size_t len); // Using preallocated block

	~Buffer();

	// ***** Getters & setters *****

	void Clear(); // Sets all to zero
	void Clear(size_t len);
	void Set(sample_t val);
	void Set(sample_t val, size_t len);
	void Set(sample_t* buf, size_t len); // doesn't take ownership
	void MoveFrom(Buffer && other); // Takes ownership; same as operator=
	void CopyFrom(sample_t* buf, size_t len);
	void CopyFrom(Buffer const& other); // same as operator=

	sample_t* Get();
	sample_t const* GetConst() const;
	size_t GetLength() const;

	// ***** Operators *****

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
	Buffer& operator/=(sample_t val);

	// math out of place
	Buffer operator-();
	friend Buffer operator+(Buffer const& lhs, Buffer const& rhs);
	friend Buffer operator+(Buffer const& lhs, sample_t rhs);
	friend Buffer operator-(Buffer const& lhs, Buffer const& rhs);
	friend Buffer operator-(Buffer const& lhs, sample_t rhs);
	friend Buffer operator*(Buffer const& lhs, Buffer const& rhs);
	friend Buffer operator*(Buffer const& lhs, sample_t rhs);
	friend Buffer operator/(Buffer const& lhs, Buffer const& rhs); /// warning: slower (see above)
	friend Buffer operator/(Buffer const& lhs, sample_t rhs);

private:
	void Dealloc_();
	void Realloc_(size_t len);

	size_t m_len;
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

inline void Buffer::Clear(size_t len) {
	if (m_len != len) Realloc_(len);
	juce::FloatVectorOperations::clear(m_p, m_len);
}

inline void Buffer::Set(sample_t val) {
	juce::FloatVectorOperations::fill(m_p, val, m_len);
}

inline void Buffer::Set(sample_t val, size_t len) {
	if (m_len != len) Realloc_(len);
	juce::FloatVectorOperations::fill(m_p, val, len);
}

inline void Buffer::CopyFrom(sample_t* buf, size_t len) {
	if (m_len != len) Realloc_(len);
	juce::FloatVectorOperations::copy(m_p, buf, m_len);
}

// same as operator=(Buffer)
inline void Buffer::CopyFrom(Buffer const& other) {
	if (m_len != other.m_len) Realloc_(other.m_len);
	juce::FloatVectorOperations::copy(m_p, other.GetConst(), m_len);
}

inline size_t Buffer::GetLength() const {
	return m_len;
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

} // namespace Utils

#endif  // BUFFER_H_INCLUDED
