#include "ingress/transaction_ingress.h"
#include "core/pipeline.h"
#include <iostream>


int main() {
	SPSCQueue<Transaction, 1024> queue;


	TransactionIngress ingress(queue);
	Pipeline pipeline(queue);


	pipeline.start();
	ingress.start();


	std::cout << "Fraud engine running... Press Enter to stop\n";
	std::cin.get();


	ingress.stop();
	pipeline.stop();
	return 0;
}