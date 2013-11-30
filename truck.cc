#include "truck.h"

// constructor
Truck::Truck(Printer& prt, NameServer& nameServer, BottlingPlant& plant,
			 unsigned int numVendingMachines, unsigned int maxStockPerFlavour):
	printer(prt),
	nameServer(nameServer),
	plant(plant)
{
	this->numVendingMachines = numVendingMachines;
	this->maxStockPerFlavour = maxStockPerFlavour;
}

// main method
void Truck::main(){
	// truck slacks off for ten cycles
	// then picks up shipment
	// then get list of machines from the fucking nameserver thing
	// then restocks each machine (as much as it can shove in)
	// goes back to plant when out of everything
	// in a loop
	// break out of loop if plant is closing
}