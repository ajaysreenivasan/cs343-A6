#ifndef BOTTLEPLANT_H
#define BOTTLEPLANT_H

#include "printer.h"
#include "nameServer.h"

_Task BottlingPlant {
public:
	BottlingPlant(Printer& prt, NameServer& nameServer, unsigned int numVendingMachines,
		unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
		unsigned int timeBetweenShipments);
	bool getShipment(unsigned int cargo[]);

private:
	void main();

private:
	Printer& printer;
	NameServer& nameServer;
	unsigned int numVendingMachines;
	unsigned int maxShippedPerFlavour;
	unsigned int maxStockPerFlavour;
	unsigned int timeBetweenShipments;
};

#endif