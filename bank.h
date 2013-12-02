#ifndef BANK_H
#define BANK_H

#include <uC++.h>


_Monitor Bank {
  public:
    Bank(unsigned int numStudents);
	~Bank();
    void deposit(unsigned int id, unsigned int amount);
    void withdraw(unsigned int id, unsigned int amount);
	
private:
	unsigned int numStudents;
	unsigned int amount;
	unsigned int* studentBalances;						//balances for each student
	uCondition* studentBalanceCondition;				//used to block on insufficient funds
};

#endif

// comment