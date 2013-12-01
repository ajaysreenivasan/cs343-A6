#include "bottlePlant.h"

// constructor
BottlingPlant::BottlingPlant(Printer& prt, NameServer& nameServer, unsigned int numVendingMachines,
							 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
							 unsigned int timeBetweenShipments):
	printer(prt),
	nameServer(nameServer)
{
	this->numVendingMachines = numVendingMachines;
	this->maxShippedPerFlavour = maxShippedPerFlavour;
	this->maxStockPerFlavour = maxStockPerFlavour;
	this->timeBetweenShipments = timeBetweenShipments;

	this->maxFlavourCount = 4; // Given in assignment. Look into changing it from magic # maybe.
	this->isClosing = false;
	this->shipment = new unsigned int[maxFlavourCount];
	this->shippingTruck = new Truck(printer, nameServer, *this,
		numVendingMachines, maxStockPerFlavour);
}

BottlingPlant::~BottlingPlant(){
	delete shipment;
}

bool BottlingPlant::getShipment(unsigned int cargo[]){
	if(isClosing){
		return true;
	}
	else{
		for(unsigned int i = 0; i < maxFlavourCount; i++){
			cargo[i] = shipment[i];
			shipment[i] = 0;
		}

		return false;
	}
}

void BottlingPlant::main(){
	while(true){
		yield(timeBetweenShipments);

		for(unsigned int i = 0; i < maxFlavourCount; i++){
			shipment[i] = rng(0, maxStockPerFlavour);
		}

		_Accept(~BottlingPlant){
			isClosing = true; 
			break;
		}
		or
		_Accept(getShipment){
			if(isClosing)
				delete shippingTruck;
		}
	}
}

// comment
// comment