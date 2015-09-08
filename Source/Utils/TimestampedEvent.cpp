/*
  ==============================================================================

    TimestampedEvent.cpp
    Created: 7 Sep 2015 10:54:51pm
    Author:  Joel

  ==============================================================================
*/

#include "TimestampedEvent.h"

namespace Utils {

template<typename Tin, typename Tout>
Tin EventBufToBuf(
	/*in*/ Tin startVal,
	/*in*/ eventBuf_t<Tin> const& inBuf,
	/*in*/ size_t length,
	/*out*/ Tout* outBuf,
	/*in*/ Tout scaleFactor,
	/*in*/ Tout offset)
{
	Tin inVal = startVal;
	Tout outVal = scaleFactor*static_cast<Tout>(startVal) + offset;

	size_t n = 0;
	for (eventBuf_t<Tin>::const_iterator it = inBuf.begin(); it != inBuf.end(); ++it)
	{
		size_t eventTime = it->time;
		while (n < eventTime) outBuf[n++] = outVal;
		inVal = it->ev;
		outVal = scaleFactor*static_cast<Tout>(inVal) + offset;
	}

	while (n < length) outBuf[n++] = outVal;

	return inVal;
}

template uint8_t EventBufToBuf<uint8_t, float>(uint8_t, eventBuf_t<uint8_t> const&, size_t, float*, float, float);
template int EventBufToBuf<int, float>(int, eventBuf_t<int> const&, size_t, float*, float, float);

}