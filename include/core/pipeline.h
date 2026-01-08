#pragma once
#include <atomic>
#include <iostream>
#include <thread>

#include "core/lockfree_queue.h"
#include "features/feature_engine.h"
#include "rules/rule_engine.h"

class Pipeline {
 public:
  explicit Pipeline(size_t workers = 4)
      : worker_count_(workers), queues_(workers) {}

  void start();
  void stop();
  void submit(const Transaction& txn);

 private:
  void worker_loop(size_t worker_id);
  size_t shard_for(const Transaction& txn) const;

  inline static std::mutex log_mutex_;

  std::vector<std::unique_ptr<FeatureEngine>> feature_engines_;
  RuleEngine rule_engine_;
  std::atomic<bool> running_{false};
  std::vector<std::thread> workers_;
  size_t worker_count_{0};
  std::vector<SPSCQueue<Transaction, 1024>> queues_;
};
