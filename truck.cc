#include "truck.h"

using namespace std;

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

}