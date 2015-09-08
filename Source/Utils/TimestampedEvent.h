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
	/*in*/ Tout scale = static_cast<Tout>(1),
	/*in*/ Tout offset = static_cast<Tout>(0));

} // namespace Utils

#endif  // TIMESTAMPEDEVENT_H_INCLUDED
