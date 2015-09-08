/*
  ==============================================================================

    Types.h
    Created: 5 Sep 2015 6:33:07pm
    Author:  Joel

  ==============================================================================
*/

#ifndef UTILS_TYPES_H_INCLUDED
#define UTILS_TYPES_H_INCLUDED

#include "Utils/Debug.h"

namespace Utils {
	typedef float sample_t;

	// Constants:
	sample_t const k_defaultApproxEqualThresh = 0.0001f;
}

#include "Utils/Buffer.h"
#include "Utils/TimestampedEvent.h"

#endif  // UTILS_TYPES_H_INCLUDED
