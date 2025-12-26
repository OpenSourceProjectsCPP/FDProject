#pragma once
#include <string>
#include <cstdint>


struct Transaction {
	std::string txn_id;
	std::string card_id;
	double amount{ 0.0 };
	std::string currency;
	std::string merchant_id;
	std::string country;
	uint64_t timestamp{ 0 }; // epoch millis
};