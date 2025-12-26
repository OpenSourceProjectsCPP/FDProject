#pragma once

#include "common/types.h"
#include "core/lockfree_queue.h"
#include <thread>
#include <atomic>


class TransactionIngress {
public:
	explicit TransactionIngress(SPSCQueue<Transaction, 1024>& q)
		: queue_(q) {
	}


	void start();
	void stop();


private:
	void run();


	std::atomic<bool> running_{ false };
	std::thread worker_;
	SPSCQueue<Transaction, 1024>& queue_;
};


