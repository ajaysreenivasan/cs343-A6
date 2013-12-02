#include "nameServer.h"
#include "vendingMachine.h"
#include <vector>

using namespace std;

// constructor
NameServer::NameServer(Printer& prt, unsigned int numVendingMachines, unsigned int numStudents):
	printer(prt)
{
	this->numVendingMachines = numVendingMachines;
	this->numStudents = numStudents;
	this->vendingMachineList = new VendingMachine*[numVendingMachines];

	for(unsigned int i = 0; i < numVendingMachines; i++){
		vendingMachineList[i] = NULL;
	}

	for(unsigned int i = 0; i < numStudents; i++){
		this->studentNextMachineAssignment.push_back(i % numVendingMachines);	// initialize indexes to be used by students
	}

	this->vmRegisteredCondition = new uCondition[numVendingMachines];
}

NameServer::~NameServer(){
	delete[] vendingMachineList; //delete arrary of pointers
}

void NameServer::VMregister(VendingMachine* vendingmachine){
	int vendingMachineId = vendingmachine->getId();
	vendingMachineList[vendingMachineId] = vendingmachine;
	vmRegisteredCondition[vendingMachineId].signal();
}

//need to ensure that all vending machines registered before running below code
VendingMachine* NameServer::getMachine(unsigned int id){
	if(vendingMachineList[id] == NULL)
		vmRegisteredCondition[id].wait();

	VendingMachine* retValue = vendingMachineList[studentNextMachineAssignment[id]];
	studentNextMachineAssignment[id] = (studentNextMachineAssignment[id] + 1) % numVendingMachines;

	return retValue;
}

VendingMachine** NameServer::getMachineList(){
	return vendingMachineList;
}

void NameServer::main(){
	while(true){	//loop infinitely until destructor called
		_Accept(~NameServer){
			break;
		}
		or
			_Accept(VMregister){
		}
		or
			_Accept(getMachine, getMachineList){
		}
	}
}