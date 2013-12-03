#ifndef NAMESERVER_H
#define NAMESERVER_H

#include "printer.h"

#include <uC++.h>
#include <vector>

_Task VendingMachine;

// declaration of NameServer
_Task NameServer {
public:
	NameServer(Printer& prt, unsigned int numVendingMachines, unsigned int numStudents);	// constructor
	~NameServer();																			// destructor
	void VMregister(VendingMachine* vendingmachine);					// register VM with nameserver
	VendingMachine* getMachine(unsigned int id);						// return a machine id 
	VendingMachine** getMachineList();									// return the list of machines

private:
	void main();

private:
	Printer& printer;
	unsigned int numVendingMachines;								// # of machines
	unsigned int numStudents;										// total # of students
	unsigned int vendingMachineIndex;								
	VendingMachine** vendingMachineList;							// stores a list of pointers to vending machines
	std::vector<int> studentNextMachineAssignment;					// used to keep track of what vendingMachine
																	// students should get next
};

#endif