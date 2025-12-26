#pragma once
#include <deque>
#include <cstdint>


struct TimedValue {
	uint64_t ts;
	double value;
};


class SlidingWindowCounter {
public:
	explicit SlidingWindowCounter(uint64_t window_ms)
		: window_ms_(window_ms) {
	}


	void add(uint64_t ts, double value = 1.0) {
		events_.push_back({ ts, value });
		cleanup(ts);
	}


	double sum(uint64_t now) {
		cleanup(now);
		double s = 0;
		for (auto& e : events_) s += e.value;
		return s;
	}


private:
	void cleanup(uint64_t now) {
		while (!events_.empty() && now - events_.front().ts > window_ms_) {
			events_.pop_front();
		}
	}


	uint64_t window_ms_;
	std::deque<TimedValue> events_;
};


struct CardState {
	SlidingWindowCounter txns_1min{ 60'000 };
	SlidingWindowCounter txns_5min{ 300'000 };
	SlidingWindowCounter amt_5min{ 300'000 };
};