#include "bank.h"

using namespace std;

Bank::Bank(unsigned int numStudents){
	this->numStudents = numStudents;

	for(unsigned int i = 0; i < numStudents; i++)
		studentBalances[i] = 0;
}

void Bank::deposit(unsigned int id, unsigned int amount){
	studentBalanceCondition[id].signal();

	studentBalances[id] += amount;
}

void Bank::withdraw(unsigned int id, unsigned int amount){
	while(studentBalances[id] < amount){
		studentBalanceCondition[id].wait();
	}

	studentBalances[id] -= amount;
}