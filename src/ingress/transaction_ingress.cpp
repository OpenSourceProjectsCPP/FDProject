#include "ingress/transaction_ingress.h"

#include <chrono>
#include <iostream>

void TransactionIngress::start() {
  running_ = true;
  worker_ = std::thread(&TransactionIngress::run, this);
}

void TransactionIngress::stop() {
  running_ = false;
  if (worker_.joinable()) worker_.join();
}

void TransactionIngress::run() {
  while (running_) {
    Transaction txn;
    txn.txn_id = "TXN-" + std::to_string(10000 + std::rand() % 10000);
    // txn.card_id = "CARD-123";
    txn.card_id = "CARD-" + std::to_string(10 + (std::rand() % 10));
    txn.amount = 100 + (std::rand() % 1000);
    txn.currency = "INR";
    txn.merchant_id = "MERCHANT-42";
    txn.country = "IN";
    txn.timestamp = static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count());

    /*if (!queue_.push(txn)) {
      std::cerr << "Ingress queue full, dropping txn\n";
    }*/
    pipeline_.submit(txn);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}
