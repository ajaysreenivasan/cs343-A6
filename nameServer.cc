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
		this->studentNextMachineAssignment.push_back(i % numVendingMachines);	// initialize indexes to be used by students
	}
}

NameServer::~NameServer(){
	delete[] vendingMachineList; //delete arrary of pointers
}

void NameServer::VMregister(VendingMachine* vendingmachine){
	printer.print(Printer::NameServer,'R',vendingmachine->getId());
	vendingMachineList[vendingMachineIndex]=vendingmachine;
	vendingMachineIndex++;
}

VendingMachine* NameServer::getMachine(unsigned int id){
	//need to ensure that all vending machines registered before running below code
	VendingMachine* retValue = vendingMachineList[studentNextMachineAssignment[id]];
	studentNextMachineAssignment[id] = (studentNextMachineAssignment[id] + 1) % numVendingMachines;
	printer.print(Printer::NameServer,'N',id,retValue->getId());
	return retValue;
}

VendingMachine** NameServer::getMachineList(){
	return vendingMachineList;
}

void NameServer::main(){
	printer.print(Printer::NameServer,'S');
	while(true){	//loop infinitely until destructor called
		_Accept(~NameServer){
			break;
		}
		or _When(vendingMachineIndex < numVendingMachines)
			_Accept(VMregister){}
		or _When(!vendingMachineIndex < numVendingMachines)
			_Accept(getMachine, getMachineList){}
	}
	printer.print(Printer::NameServer,'F');
}