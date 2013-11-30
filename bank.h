#ifndef BANK_H
#define BANK_H

#include <uC++.h>
#include <vector>

_Monitor Bank {
  public:
    Bank(unsigned int numStudents);
    void deposit(unsigned int id, unsigned int amount);
    void withdraw(unsigned int id, unsigned int amount);
	
private:
	unsigned int numStudents;
	unsigned int amount;
	std::vector<unsigned int> studentBalances;
	std::vector<uCondition> studentBalanceCondition;
};

#endif