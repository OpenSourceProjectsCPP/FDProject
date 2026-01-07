#include <iostream>

#include "core/pipeline.h"
#include "ingress/transaction_ingress.h"

int main() {
  Pipeline pipeline(4);
  TransactionIngress ingress(pipeline);

  pipeline.start();
  ingress.start();

  std::cout << "Fraud engine running... Press Enter to stop\n";
  std::cin.get();

  ingress.stop();
  pipeline.stop();
  return 0;
}
