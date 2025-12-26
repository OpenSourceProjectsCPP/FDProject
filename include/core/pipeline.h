#pragma once
#include "core/lockfree_queue.h"
#include "features/feature_engine.h"
#include <thread>
#include <atomic>
#include <iostream>


class Pipeline {
public:
	explicit Pipeline(SPSCQueue<Transaction, 1024>& q)
		: queue_(q) {
	}


	void start();
	void stop();


private:
	void run();


	FeatureEngine feature_engine_;
	std::atomic<bool> running_{ false };
	std::thread worker_;
	SPSCQueue<Transaction, 1024>& queue_;
};