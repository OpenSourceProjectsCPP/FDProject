#pragma once

#include <atomic>
#include <thread>

#include "common/types.h"
#include "core/lockfree_queue.h"
#include "core/pipeline.h"

class TransactionIngress {
 public:
  explicit TransactionIngress(Pipeline& p) : pipeline_(p) {}

  void start();
  void stop();

 private:
  void run();

  std::atomic<bool> running_{false};
  std::thread worker_;
  Pipeline& pipeline_;
};
