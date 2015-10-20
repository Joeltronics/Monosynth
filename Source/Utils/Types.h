/*
  ==============================================================================

    Types.h
    Created: 5 Sep 2015 6:33:07pm
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

#ifndef UTILS_TYPES_H_INCLUDED
#define UTILS_TYPES_H_INCLUDED

#include "Utils/Debug.h"

#include <array>
#include <algorithm>

namespace Utils {
	typedef float sample_t;

	// Constants:
	sample_t const k_defaultApproxEqualThresh = 0.0001f;

	template <typename T>
	class Range_t {
	public:

		T const min;
		T const max;

		// If values given are backward, will swap them
		Range_t(T min_, T max_) :
			min((min_ <= max_) ? min_ : max_),
			max((min_ <= max_) ? max_ : min_)
		{}
		
		// If values given are backward, will swap them
		Range_t(std::array<T, 2> arr) :
			min((arr[0] <= arr[1]) ? arr[0] : arr[1]),
			max((arr[0] <= arr[1]) ? arr[1] : arr[0])
		{}

		Range_t(Range_t const& r) :
			min(r.min),
			max(r.max)
		{}

		friend bool operator==(Range_t<T> const& lhs, Range_t<T> const& rhs);
		friend bool operator!=(Range_t<T> const& lhs, Range_t<T> const& rhs);

		bool IsInRange(T val) const {
			return (val <= max && val >= min);
		}

		T Clip(T val) const {
			return std::max(std::min(val, max), min);
		}
	};

	template <typename T>
	inline bool operator==(Range_t<T> const& lhs, Range_t<T> const& rhs) {
		return (lhs.min == rhs.min && lhs.max == rhs.max);
	}

	template <typename T>
	inline bool operator!=(Range_t<T> const& lhs, Range_t<T> const& rhs) {
		return (lhs.min != rhs.min || lhs.max != rhs.max);
	}
}

#include "Utils/Buffer.h"
#include "Utils/TimestampedEvent.h"

#endif  // UTILS_TYPES_H_INCLUDED
