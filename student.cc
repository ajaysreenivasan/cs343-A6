#include "student.h"

using namespace std;

// constructor
Student::Student( Printer& prt, NameServer& nameServer, WATCardOffice& cardOffice, unsigned int id,
				 unsigned int maxPurchases ):
printer(prt),
	nameServer(nameServer),
	cardOffice(cardOffice)
{
	this->id = id;
	this->maxPurchases = maxPurchases;
}

void Student::main(){

}