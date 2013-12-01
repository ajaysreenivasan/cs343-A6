#include "bank.h"

using namespace std;

Bank::Bank(unsigned int numStudents){								//constructor
	this->numStudents = numStudents;

	for(unsigned int i = 0; i < numStudents; i++)
		studentBalances[i] = 0;										//init balances to 0 for each student
}

void Bank::deposit(unsigned int id, unsigned int amount){
	studentBalanceCondition[id].signal();							//signal any tasks waiting on balance to update

	studentBalances[id] += amount;									//deposit amount
}

void Bank::withdraw(unsigned int id, unsigned int amount){			
	while(studentBalances[id] < amount){							//while insufficient funds block
		studentBalanceCondition[id].wait();
	}

	studentBalances[id] -= amount;									//withdraw amount
}