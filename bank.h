#ifndef BANK_H
#define BANK_H

#include <uC++.h>

// declaration of Bank
_Monitor Bank {
  public:
    Bank(unsigned int numStudents);						// constructor
	~Bank();											// destructor
    void deposit(unsigned int id, unsigned int amount);	
    void withdraw(unsigned int id, unsigned int amount);
	
private:
	unsigned int numStudents;							// # of students
	unsigned int amount;								// amount of money to deposit or withdraw
	unsigned int* studentBalances;						// balances for each student
	uCondition* studentBalanceCondition;				// used to block on insufficient funds
};

#endif