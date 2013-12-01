#include "nameServer.h"
#include "vendingMachine.h"
#include <vector>

using namespace std;

																										// constructor
NameServer::NameServer(Printer& prt, unsigned int numVendingMachines, unsigned int numStudents):
	printer(prt)
{
	this->numVendingMachines = numVendingMachines;														//setting member values
	this->numStudents = numStudents;
	this->vendingMachineList = new VendingMachine*[numVendingMachines];
	this->vendingMachineIndex = 0;
	
	for(unsigned int i = 0; i < numStudents; i++){
		this->studentNextMachineAssignment.push_back(i % numVendingMachines);							// initialize indexes to be used by students
	}
}

NameServer::~NameServer(){																				//destructor
	delete[] vendingMachineList; 																		//delete arrary of pointers
}

void NameServer::VMregister(VendingMachine* vendingmachine){
	vendingMachineList[vendingMachineIndex++]=vendingmachine;											//add vendingmachine to vendingMachineList
}

VendingMachine* NameServer::getMachine(unsigned int id){												//return next vending machine for specified user on round robin
	VendingMachine* retValue = vendingMachineList[studentNextMachineAssignment[id]];
	studentNextMachineAssignment[id] = (studentNextMachineAssignment[id] + 1) % numVendingMachines;
	
	return retValue;
}

VendingMachine** NameServer::getMachineList(){															//return pointer to array of vending machine pointers
	return vendingMachineList;
}

void NameServer::main(){																				//loop until destructor called
	while(true){
		_Accept(~NameServer){	
			break;
		}

		if(vendingMachineIndex < numVendingMachines)													//if not all vending machines are registered only accept VMregister 
			_Accept(VMregister);
		else
			_Accept(getMachine, getMachineList);														//when all vending machines are registered accept getMachine and getMachineList
	}
}