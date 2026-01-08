#include "rules/rule_engine.h"

std::vector<RuleResult> RuleEngine::evaluate(const FeatureVector& fv) const {
  std::vector<RuleResult> results;
  // Example rule: High transaction velocity in last 1 min
  if (fv.get("txn_count_1min") > 300) {
    results.push_back(
        {"R1_VELOCITY_1MIN", 30, "High transaction velocity in last 1 min"});
  }
  // Example rule: High spend in last 5 min
  if (fv.get("amount_sum_5min") > 20000) {
    results.push_back({"R2_AMOUNT_5MIN", 40, "High spend in last 5 min"});
  }
  return results;
}
