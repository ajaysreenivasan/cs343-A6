#ifndef TRUCK_H
#define TRUCK_H

#include "printer.h"
#include "nameServer.h"
#include "bottlePlant.h"

_Task BottlingPlant;

// declaration of truck
_Task Truck {
public:
	// constructor
	Truck(Printer& prt, NameServer& nameServer, BottlingPlant& plant,	
		unsigned int numVendingMachines, unsigned int maxStockPerFlavour);
	~Truck();	// destructor

private:
	void main();
	void checkCargo();					// checks if the truck still has something in cargo
	unsigned int getCargoCount();		// counts the truck's remaining cargo

private:
	Printer& printer;
	NameServer& nameServer;
	BottlingPlant& plant;
	unsigned int numVendingMachines;	// # of vending machines
	unsigned int maxStockPerFlavour;	// max # of bottles per flavour
	unsigned int* cargo;				
	bool hasCargo;						// tracks if truck has cargo
};

#endif
