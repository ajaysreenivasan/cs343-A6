#include "parent.h"

using namespace std;

// constructo
Parent::Parent(Printer& prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay): 
	printer(prt),
	bank(bank)
{
	this->numStudents = numStudents;
	this->parentalDelay = parentalDelay;
}

void Parent::main(){

}