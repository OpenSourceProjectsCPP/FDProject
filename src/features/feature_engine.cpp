#include "features/feature_engine.h"

FeatureVector FeatureEngine::extract(const Transaction& txn) {
  auto& shard = shard_for(txn.card_id);
  std::lock_guard<std::mutex> lock(shard.mtx);

  auto& state = shard.state[txn.card_id];

  state.txns_1min.add(txn.timestamp);
  state.txns_5min.add(txn.timestamp);
  state.amt_5min.add(txn.timestamp, txn.amount);

  FeatureVector fv;
  fv.values["txn_count_1min"] = state.txns_1min.sum(txn.timestamp);
  fv.values["txn_count_5min"] = state.txns_5min.sum(txn.timestamp);
  fv.values["amount_sum_5min"] = state.amt_5min.sum(txn.timestamp);

  return fv;
}
