#include "nameServer.h"
#include "vendingMachine.h"
#include <vector>
#include <iostream>

using namespace std;

																									// constructor
NameServer::NameServer(Printer& prt, unsigned int numVendingMachines, unsigned int numStudents):
	printer(prt)
{
	this->numVendingMachines = numVendingMachines;
	this->numStudents = numStudents;
	this->vendingMachineList = new VendingMachine*[numVendingMachines];
	this->vendingMachineIndex = 0;
	
	for(unsigned int i = 0; i < numStudents; i++){
		this->studentNextMachineAssignment.push_back(i % numVendingMachines);						// initialize indexes to be used by students
	}
}

NameServer::~NameServer(){
	delete[] vendingMachineList; 																	//delete pointer to arrary of pointers
}

void NameServer::VMregister(VendingMachine* vendingmachine){										//register vendingmachines in indexes they appear
	printer.print(Printer::NameServer,'R',vendingmachine->getId());
	vendingMachineList[vendingMachineIndex]=vendingmachine;
	vendingMachineIndex++;
}

VendingMachine* NameServer::getMachine(unsigned int id){											//return pointer to vending machine for specific user based on round robin strategy
	VendingMachine* retValue = vendingMachineList[studentNextMachineAssignment[id]];
	studentNextMachineAssignment[id] = (studentNextMachineAssignment[id] + 1) % numVendingMachines;
	printer.print(Printer::NameServer,'N',id,retValue->getId());
	return retValue;
}

VendingMachine** NameServer::getMachineList(){
	return vendingMachineList;
}

void NameServer::main(){
	printer.print(Printer::NameServer,'S');															//main
	while(true){																					//loop infinitely until destructor called
		_Accept(~NameServer){
			break;
		}
		or _When(vendingMachineIndex < numVendingMachines)											//only accept calls to getMachine and getMachineList after all vending machines registered
			_Accept(VMregister){}
		or _When(!vendingMachineIndex < numVendingMachines)
			_Accept(getMachine, getMachineList){}
	}
	printer.print(Printer::NameServer,'F');
}