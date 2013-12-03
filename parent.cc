#include "parent.h"

// constructor
Parent::Parent(Printer& prt, Bank& bank, unsigned int numStudents, unsigned int parentalDelay): 
	printer(prt),
	bank(bank)
{
	this->numStudents = numStudents;
	this->parentalDelay = parentalDelay;
}

// accepts destructor and breaks out of loop
// otherwise loops forever and randomly deposits money into a random student's account
void Parent::main(){								// main loop until destructor called
	printer.print(Printer::Parent,'S');
	
	while(true){
		_Accept(~Parent){
			break;
		}
		_Else{ 	//deposit random amount of money for random student id after yeilding parentalDelay times
			unsigned int depositRecipient = rng(0, numStudents - 1);						
			unsigned int depositAmount = rng(1, 3);
			yield(parentalDelay);
			printer.print(Printer::Parent,'D',depositRecipient,depositAmount);
			bank.deposit(depositRecipient, depositAmount);
		}
	}

	printer.print(Printer::Parent,'F');
}
