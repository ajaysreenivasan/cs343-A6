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
	vendingMachineIndex=0;
	for(unsigned int i=0;i<numStudents;i++){
		this->studentNextMachineAssignment.push_back(i%numVendingMachines);	// initialize indexes to be used by students
	}
}

NameServer::~NameServer(){
	delete[] vendingMachineList; //delete arrary of pointers
}

void NameServer::VMregister(VendingMachine* vendingmachine){
	vendingMachineList[vendingMachineIndex++]=vendingmachine;
}

VendingMachine* NameServer::getMachine(unsigned int id){
	//need to ensure that all vending machines registered before running below code
	VendingMachine* retValue = vendingMachineList[studentNextMachineAssignment[id]];
	studentNextMachineAssignment[id]=(studentNextMachineAssignment[id]+1)%numVendingMachines;
	return retValue;
}

VendingMachine** NameServer::getMachineList(){
	return vendingMachineList;
}

void NameServer::main(){
	while(true){	//loop infinitely until destructor called
		_Accept(NameServer::~NameServer){
			break;
		}
		if(vendingMachineIndex<numVendingMachines) 
			_Accept(NameServer::VMregister);
		else
			_Accept(NameServer::getMachine, NameServer::getMachineList);

	}
}