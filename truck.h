#ifndef TRUCK_H
#define TRUCK_H

#include "printer.h"
#include "nameServer.h"
#include "bottlePlant.h"

_Task BottlingPlant;

_Task Truck {
public:
	Truck(Printer& prt, NameServer& nameServer, BottlingPlant& plant,
		unsigned int numVendingMachines, unsigned int maxStockPerFlavour);
	~Truck();

private:
	void main();
	void checkCargo();

private:
	Printer& printer;
	NameServer& nameServer;
	BottlingPlant& plant;
	unsigned int numVendingMachines;
	unsigned int maxStockPerFlavour;
	unsigned int* cargo;
	bool hasCargo;
};

#endif

// comment
// comment