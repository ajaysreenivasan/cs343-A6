#include "nameServer.h"
#include "vendingMachine.h"

using namespace std;

// constructor
NameServer::NameServer(Printer& prt, unsigned int numVendingMachines, unsigned int numStudents):
	printer(prt)
{
	this->numVendingMachines = numVendingMachines;
	this->numStudents = numStudents;

	this->vendingMachineList = new VendingMachine*[numVendingMachines];
}

NameServer::~NameServer(){
	delete vendingMachineList;
}

void NameServer::VMregister(VendingMachine* vendingmachine){
	//this->vendingMachineList->push_back(vendingmachine);
}

VendingMachine* NameServer::getMachine(unsigned int id){
	//return this->vendingMachineList[id];
	return NULL;
}

VendingMachine** NameServer::getMachineList(){
	//return vendingMachineList;
	return NULL;
}

void NameServer::main(){

}

// comment
// comment