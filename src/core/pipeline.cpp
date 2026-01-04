#include "core/pipeline.h"

void Pipeline::start() {
  running_ = true;
  worker_ = std::thread(&Pipeline::run, this);
}

void Pipeline::stop() {
  running_ = false;
  if (worker_.joinable()) worker_.join();
}

void Pipeline::run() {
  while (running_) {
    auto opt = queue_.pop();
    if (!opt) continue;

    const Transaction& txn = *opt;
    auto features = feature_engine_.extract(txn);

    std::cout << "Txn " << txn.txn_id << " Card=" << txn.card_id
              << " f1=" << features.get("txn_count_1min")
              << " f5=" << features.get("txn_count_5min")
              << " amt5=" << features.get("amount_sum_5min") << '\n';
  }
}
