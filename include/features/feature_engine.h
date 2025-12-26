#pragma once
#include "common/types.h"
#include "common/feature_vector.h"
#include "features/card_state.h"
#include <unordered_map>


class FeatureEngine {
public:
	FeatureVector extract(const Transaction& txn);


private:
	std::unordered_map<std::string, CardState> card_state_;
};