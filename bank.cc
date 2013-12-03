#include "bank.h"

// constructor
// assigns passed in values to appropriate member variables
// initializes member variables
Bank::Bank(unsigned int numStudents){								//constructor
	this->numStudents = numStudents;

	this->studentBalances = new unsigned int[numStudents];
	for(unsigned int i = 0; i < numStudents; i++)
		studentBalances[i] = 0;	 									// init balances to 0 for each student
	
	this->studentBalanceCondition = new uCondition[numStudents];	// initializes condition variables for each student
}

// destructor
Bank::~Bank(){
	delete[] studentBalances;				// delete student balances
	delete[] studentBalanceCondition;		// delete condition variables
}

// parent deposits money into student's bank account
void Bank::deposit(unsigned int id, unsigned int amount){
	studentBalanceCondition[id].signal();							// signal any tasks waiting on balance to update

	studentBalances[id] += amount;									// deposit amount
}

// courier withdraws money from student's account for deposit into student's card
void Bank::withdraw(unsigned int id, unsigned int amount){			
	while(studentBalances[id] < amount){							// while insufficient funds block
		studentBalanceCondition[id].wait();
	}

	studentBalances[id] -= amount;									// withdraw amount
}