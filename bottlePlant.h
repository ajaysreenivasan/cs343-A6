#ifndef BOTTLEPLANT_H
#define BOTTLEPLANT_H

#include "MPRNG.h"

#include "printer.h"
#include "nameServer.h"
#include "truck.h"
#include "vendingMachine.h"

extern MPRNG rng;

_Task Truck;

_Task BottlingPlant {
public:
	BottlingPlant(Printer& prt, NameServer& nameServer, unsigned int numVendingMachines,
		unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
		unsigned int timeBetweenShipments);
	~BottlingPlant();
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
	bool isClosing;
	unsigned int* shipment;
	Truck* shippingTruck;
};

#endif

// comment