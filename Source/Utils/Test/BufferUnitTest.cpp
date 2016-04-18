/*
  ==============================================================================

    BufferUnitTest.cpp
    Created: 9 Apr 2016 5:07:47pm
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

#include "BufferUnitTest.h"
#include "Utils/Buffer.h"
#include "Utils/ApproxEqual.h"

using namespace Utils;

namespace Test {

BufferUnitTest::BufferUnitTest()
	: UnitTest("Buffer unit test")
{}

void BufferUnitTest::runTest()
{
	juce::Random juceRand = getRandom();

	auto rand = [&]() {
		return juceRand.nextFloat() * 200.0f - 100.0f;
	};

	auto randNonZero = [&]() {
		sample_t const k_minVal = 0.0001f;
		sample_t val = rand();
		if (abs(val) < k_minVal) {
			return (val >= 0.0f) ? k_minVal : -k_minVal;
		}
		return val;
	};

	beginTest("Testing buffer reallocation");
	{
		size_t const origLen = 50;
		size_t const origAllocLen = 73;
		size_t const smallerLen = 30;
		size_t const newLen = 80;

		Utils::sample_t setVal = 1.0f;

		// Original allocation: size should be 50/73
		Buffer testBuf(origLen, origAllocLen);
		sample_t const* origPtr = testBuf.GetConst();
		testBuf.Set(setVal++);
		expect(testBuf.GetLength() == origLen);
		expect(testBuf.GetAllocLength() == origAllocLen);

		// Resize without realloc: size should be 30/73, ptr shouldn't move
		testBuf.Resize(smallerLen, false);
		testBuf.Set(setVal++);
		expect(testBuf.GetLength() == smallerLen);
		expect(testBuf.GetAllocLength() == origAllocLen);
		expect(origPtr == testBuf.GetConst());

		// Resize without realloc: size should be 50/73, ptr shouldn't move
		testBuf.Resize(origLen, false);
		testBuf.Set(setVal++);
		expect(testBuf.GetLength() == origLen);
		expect(testBuf.GetAllocLength() == origAllocLen);
		expect(origPtr == testBuf.GetConst());

		// Resize with realloc: size should be 30/30, ptr may or may not move
		testBuf.Resize(smallerLen, true);
		testBuf.Set(setVal++);
		expect(testBuf.GetLength() == smallerLen);
		expect(testBuf.GetAllocLength() == smallerLen);

		// Resize with realloc: size should be 80/80, ptr may or may not move
		testBuf.Resize(80, false);
		testBuf.Set(setVal++);
		expect(testBuf.GetLength() == 80);
		expect(testBuf.GetAllocLength() == 80);
	}

	beginTest("Testing BufferOrVal");
	{
		size_t const k_bufLen = 256;
		Buffer srcBuf1(k_bufLen);
		Buffer srcBuf2(k_bufLen);
		BufferOrVal srcBV1(k_bufLen);
		BufferOrVal srcBV2(k_bufLen);
		
		sample_t* pBuf1 = srcBuf1.Get();
		sample_t* pBuf2 = srcBuf2.Get();

		{
			for (size_t n = 0; n < k_bufLen; ++n) {
				pBuf1[n] = rand();
				pBuf2[n] = rand();
			}
			srcBV1.SetBuffer();
			srcBV2.SetBuffer();
			srcBV1.GetBuf().CopyFrom(srcBuf1);
			srcBV2.GetBuf().CopyFrom(srcBuf2);
		}

		BufferOrVal testBV(k_bufLen);

		sample_t const k_val = -5.0f;
		sample_t const k_val2 = 3.14f;

		// Val *= Buf

		testBV.SetVal(k_val);

		testBV *= srcBV1;

		expect(!testBV.IsVal());
		if (!testBV.IsVal()) {
			bool bPass = true;
			sample_t const* pBv = testBV.GetBufConstPtr();
			for (size_t n = 0; n < k_bufLen; ++n) {
				if (!ApproxEqual(pBv[n], k_val*pBuf1[n])) { bPass = false; break; }
			}
			expect(bPass);
		}

		// Buf *= Buf

		testBV.SetBuffer();
		expect(!testBV.IsVal());
		testBV.GetBuf().CopyFrom(srcBuf2);
		
		testBV *= srcBV1;
		
		if (!testBV.IsVal()) {
			bool bPass = true;
			sample_t const* pBv = testBV.GetBufConstPtr();
			for (size_t n = 0; n < k_bufLen; ++n) {
				if (!ApproxEqual(pBv[n], pBuf1[n]*pBuf2[n])) { bPass = false; break; }
			}
			expect(bPass);
		}

		// Buf *= Val

		srcBV1.SetVal(k_val);
		testBV.GetBuf().CopyFrom(srcBuf1);

		testBV *= srcBV1;

		if (!testBV.IsVal()) {
			bool bPass = true;
			sample_t const* pBv = testBV.GetBufConstPtr();
			for (size_t n = 0; n < k_bufLen; ++n) {
				if (!ApproxEqual(pBv[n], pBuf1[n] * k_val)) { bPass = false; break; }
			}
			expect(bPass);
		}

		// Val *= Val

		testBV.SetVal(k_val2);
		DEBUG_ASSERT(srcBV1.IsVal());
		testBV *= srcBV1;
		expect(testBV.IsVal());
		if (testBV.IsVal()) {
			expect(Utils::ApproxEqual(testBV.GetVal(), k_val*k_val2));
		}

		// TODO: test other operations too!
	}
}

} // namespace Test