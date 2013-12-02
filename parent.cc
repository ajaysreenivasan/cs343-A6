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
	printer.print(Printer::Parent,'S');
	while(true){
		_Accept(~Parent){
			break;
		}
		_Else{
			unsigned int depositRecipient = rng(0, numStudents - 1);
			unsigned int depositAmount = rng(1, 3);
			yield(parentalDelay);
			//printer.print(Printer::Parent,'D',depositRecipient,depositAmount);
			bank.deposit(depositRecipient, depositAmount);
		}
	}
	printer.print(Printer::Parent,'F');
}

// comment
// comment