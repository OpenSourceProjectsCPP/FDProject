#include "core/pipeline.h"

void Pipeline::start() {
  running_ = true;
  feature_engines_.reserve(worker_count_);
  for (rsize_t i = 0; i < worker_count_; ++i) {
    feature_engines_.emplace_back(std::make_unique<FeatureEngine>());
  }

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

size_t Pipeline::shard_for(const Transaction& txn) const {
  return std::hash<std::string>{}(txn.card_id) % worker_count_;
}

void Pipeline::submit(const Transaction& txn) {
  auto shard = shard_for(txn);
  while (!queues_[shard].push(txn)) {  // busy wait
                                       // backpressure / spin
  }
}

void Pipeline::worker_loop(size_t worker_id) {
  auto& queue = queues_[worker_id];
  auto& feature_engine = *feature_engines_[worker_id];
  while (running_) {
    auto opt = queue.pop();
    if (!opt) continue;

    const Transaction& txn = *opt;
    auto features = feature_engine.extract(txn);

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
