#pragma once
#include <atomic>
#include <iostream>
#include <thread>

#include "core/lockfree_queue.h"
#include "features/feature_engine.h"

class Pipeline {
 public:
  inline static std::mutex log_mutex_;

 public:
  explicit Pipeline(SPSCQueue<Transaction, 1024>& q, size_t workers = 4)
      : queue_(q), worker_count_(workers) {}

  void start();
  void stop();

 private:
  void worker_loop(size_t worker_id);

  FeatureEngine feature_engine_;
  std::atomic<bool> running_{false};
  std::vector<std::thread> workers_;
  size_t worker_count_{0};
  SPSCQueue<Transaction, 1024>& queue_;
};
