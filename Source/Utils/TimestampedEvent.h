/*
  ==============================================================================

    TimestampedEvent.h
    Created: 7 Sep 2015 10:22:46pm
    Author:  Joel

  ==============================================================================
*/

#ifndef TIMESTAMPEDEVENT_H_INCLUDED
#define TIMESTAMPEDEVENT_H_INCLUDED

#include <vector>
#include <functional>

namespace Utils {

// Timed event queues
template<typename E>
struct timedEvent_t {
	size_t time;
	E ev;

	timedEvent_t(size_t time_, E ev_) :
		time(time_), ev(ev_) {}
};

template<class T> using eventBuf_t = std::vector<timedEvent_t<T>>;

template<typename Tin, typename Tout>
Tin EventBufToBuf(
	/*in*/ Tin startVal,
	/*in*/ eventBuf_t<Tin> const& inBuf,
	/*in*/ size_t length,
	/*out*/ Tout* outBuf,
	std::function<Tout(Tin)> mappingFunc)
{
	Tin inVal = startVal;
	Tout outVal = mappingFunc(inVal);

	size_t n = 0;
	for (typename eventBuf_t<Tin>::const_iterator it = inBuf.begin(); it != inBuf.end(); ++it)
	{
		size_t eventTime = it->time;
		while (n < eventTime) outBuf[n++] = outVal;
		inVal = it->ev;
		outVal = mappingFunc(inVal);
	}

	while (n < length) outBuf[n++] = outVal;

	return inVal;
}

template<typename Tin, typename Tout>
inline Tin EventBufToBuf(
	/*in*/ Tin startVal,
	/*in*/ eventBuf_t<Tin> const& inBuf,
	/*in*/ size_t length,
	/*out*/ Tout* outBuf)
{
	std::function<Tout(Tin)> mappingFunc = [](Tin x) -> Tout {
		return static_cast<Tout>(x);
	};

	return EventBufToBuf(startVal, inBuf, length, outBuf, mappingFunc);
}

} // namespace Utils

#endif  // TIMESTAMPEDEVENT_H_INCLUDED
