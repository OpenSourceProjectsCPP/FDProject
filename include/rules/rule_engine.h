#pragma once
#include <vector>

#include "common/feature_vector.h"

struct RuleResult {
  std::string rule_id;
  int score;
  std::string explaination;
};

class RuleEngine {
 public:
  std::vector<RuleResult> evaluate(const FeatureVector& fv) const;
};
