#include "nameServer.h"
#include "vendingMachine.h"
													
// constructor
// init passed in values to appropriate member variables
// init other member variabes
NameServer::NameServer(Printer& prt, unsigned int numVendingMachines, unsigned int numStudents):
	printer(prt)
{
	this->numVendingMachines = numVendingMachines;
	this->numStudents = numStudents;
	this->vendingMachineList = new VendingMachine*[numVendingMachines];					// init list of vending machines
	this->vendingMachineIndex = 0;
	
	for(unsigned int i = 0; i < numStudents; i++){
		this->studentNextMachineAssignment.push_back(i % numVendingMachines);			// initialize indexes to be used by students
	}
}

// destructor
// delete list of vending machines
NameServer::~NameServer(){
	delete[] vendingMachineList; 																	
}

// register a machine w/ the server in the indexes that they appear
void NameServer::VMregister(VendingMachine* vendingmachine){										
	printer.print(Printer::NameServer,'R',vendingmachine->getId());
	vendingMachineList[vendingMachineIndex]=vendingmachine;
	vendingMachineIndex++;
}

// return pointer to vending machine for specific user based on round robin strategy
VendingMachine* NameServer::getMachine(unsigned int id){											
	VendingMachine* retValue = vendingMachineList[studentNextMachineAssignment[id]];
	studentNextMachineAssignment[id] = (studentNextMachineAssignment[id] + 1) % numVendingMachines;
	printer.print(Printer::NameServer,'N',id,retValue->getId());
	return retValue;
}

// retrieve list of vending machines
VendingMachine** NameServer::getMachineList(){
	return vendingMachineList;
}

// loop until destructor is called, then break
// otherwise only accept VMRegister when not all machines are registered
// when all machines are registered, accept getMachine or getMachineList
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