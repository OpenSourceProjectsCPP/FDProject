#include "core/pipeline.h"

void Pipeline::start() {
  running_ = true;
  for (size_t i = 0; i < worker_count_; ++i) {
    workers_.emplace_back(&Pipeline::worker_loop, this, i);
  }
}

void Pipeline::stop() {
  running_ = false;
  for (auto& w : workers_) {
    if (w.joinable()) w.join();
  }
}

void Pipeline::worker_loop(size_t worker_id) {
  while (running_) {
    auto opt = queue_.pop();
    if (!opt) continue;
    const Transaction& txn = *opt;
    auto features = feature_engine_.extract(txn);
    {
      std::lock_guard<std::mutex> lock(log_mutex_);
      std::cout << "[W " << worker_id << "] "
                << "Txn " << txn.txn_id << " Card=" << txn.card_id
                << " f1=" << features.get("txn_count_1min")
                << " f5=" << features.get("txn_count_5min")
                << " amt5=" << features.get("amount_sum_5min") << '\n';
    }
  }
}
