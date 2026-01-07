#pragma once
#include <array>
#include <mutex>
#include <unordered_map>

#include "common/feature_vector.h"
#include "common/types.h"
#include "features/card_state.h"

// Sharded FeatureEngine for multi-thread scalability
class FeatureEngine {
 public:
  FeatureVector extract(const Transaction& txn);

 private:
  static constexpr size_t SHARDS = 16;
  struct Shard {
    std::unordered_map<std::string, CardState> state;
    std::mutex mtx;
  };

  std::array<Shard, SHARDS> shards_;

  Shard& shard_for(const std::string& card_id) {
    size_t h = std::hash<std::string>{}(card_id);
    return shards_[h % SHARDS];
  }
};
