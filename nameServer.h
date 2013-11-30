#ifndef NAMESERVER_H
#define NAMESERVER_H

#include "printer.h"

#include <uC++.h>
#include <vector>

_Task VendingMachine;

_Task NameServer {
public:
	NameServer(Printer& prt, unsigned int numVendingMachines, unsigned int numStudents);
	~NameServer();
	void VMregister(VendingMachine* vendingmachine);
	VendingMachine* getMachine(unsigned int id);
	VendingMachine** getMachineList();

private:
	void main();

private:
	Printer& printer;
	unsigned int numVendingMachines;
	unsigned int numStudents;
	std::vector<VendingMachine*>* vendingMachineList;
};

#endif