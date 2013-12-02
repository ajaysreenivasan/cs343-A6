#include "parent.h"

// constructor
Parent::Parent(Printer& prt, Bank& bank, unsigned int numStudents, unsigned int parentalDelay): 
	printer(prt),
	bank(bank)
{
	this->numStudents = numStudents;
	this->parentalDelay = parentalDelay;
}

void Parent::main(){
	while(true){
		_Accept(~Parent){
			break;
		}
		_Else{
			unsigned int depositRecipient = rng(0, numStudents - 1);
			unsigned int depositAmount = rng(1, 3);
			yield(parentalDelay);
			bank.deposit(depositRecipient, depositAmount);
		}
	}
}

// comment
// comment