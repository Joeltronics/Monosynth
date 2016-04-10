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

namespace Test {

BufferUnitTest::BufferUnitTest()
	: UnitTest("Buffer unit test")
{}

void BufferUnitTest::runTest()
{
	beginTest("Testing buffer reallocation");
	{
		size_t const origLen = 50;
		size_t const origAllocLen = 73;
		size_t const smallerLen = 30;
		size_t const newLen = 80;

		Utils::sample_t setVal = 1.0f;

		// Original allocation: size should be 50/73
		Utils::Buffer testBuf(origLen, origAllocLen);
		Utils::sample_t const* origPtr = testBuf.GetConst();
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
}

} // namespace Test