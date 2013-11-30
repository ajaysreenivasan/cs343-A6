#ifndef TRUCK_H
#define TRUCK_H

#include "printer.h"
#include "nameServer.h"
#include "bottlePlant.h"

_Task Truck {
public:
	Truck(Printer& prt, NameServer& nameServer, BottlingPlant& plant,
		unsigned int numVendingMachines, unsigned int maxStockPerFlavour);

private:
	void main();

private:
	Printer& printer;
	NameServer& nameServer;
	BottlingPlant& plant;
	unsigned int numVendingMachines;
	unsigned int maxStockPerFlavour;
};

#endif