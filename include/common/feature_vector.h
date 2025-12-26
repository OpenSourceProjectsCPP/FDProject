#pragma once
#include <unordered_map>
#include <string>

struct FeatureVector {
	std::unordered_map<std::string, double> values;

	double get(const std::string& k) const {
		auto it = values.find(k);
		return it == values.end() ? 0.0 : it->second;
	}
};