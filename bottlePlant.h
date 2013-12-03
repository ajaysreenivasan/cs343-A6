#ifndef BOTTLEPLANT_H
#define BOTTLEPLANT_H

#include "MPRNG.h"

#include "printer.h"
#include "nameServer.h"
#include "truck.h"
#include "vendingMachine.h"

extern MPRNG rng;

_Task Truck;

// declaration of bottlingplant
_Task BottlingPlant {
public:
	// constructor
	BottlingPlant(Printer& prt, NameServer& nameServer, unsigned int numVendingMachines,
		unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
		unsigned int timeBetweenShipments);
	~BottlingPlant();							// destructor
	bool getShipment(unsigned int cargo[]);		// called by truck to pick up the shipment

private:
	void main();

private:
	Printer& printer;
	NameServer& nameServer;
	unsigned int numVendingMachines;			// # of vending machines
	unsigned int maxShippedPerFlavour;			// max # of sodas shipped per flavour
	unsigned int maxStockPerFlavour;
	unsigned int timeBetweenShipments;			// time between each shipment
	bool isClosing;								// tracks if the plant is closing
	unsigned int* shipment;						// tracks shipments
	Truck* shippingTruck;						// points to the delivery truck
};

#endif