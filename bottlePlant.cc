#include "bottlePlant.h"

// constructor
// assign values to appropriate member variables
// init member variables
BottlingPlant::BottlingPlant(Printer& prt, NameServer& nameServer, unsigned int numVendingMachines,
							 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
							 unsigned int timeBetweenShipments):
	printer(prt),
	nameServer(nameServer)
{
	this->numVendingMachines = numVendingMachines;					//setting member values
	this->maxShippedPerFlavour = maxShippedPerFlavour;
	this->maxStockPerFlavour = maxStockPerFlavour;
	this->timeBetweenShipments = timeBetweenShipments;

	this->isClosing = false;
	this->shipment = new unsigned int[VendingMachine::MAXFLAVOURCOUNT];				//creating shippment
	this->shippingTruck = new Truck(printer, nameServer, *this,						//creating truck
		numVendingMachines, maxStockPerFlavour);
}

//deconstructor
// delete shipment and truck
BottlingPlant::~BottlingPlant(){									
	delete[] shipment;
	delete shippingTruck;
}

// retrieves the shipment and pushes it into the truck
bool BottlingPlant::getShipment(unsigned int cargo[]){				// if plant closing down return true, no new shipment 4 truck
	if(isClosing){
		return true;
	}
	else{															// else copy shipment into the truck and return false
		for(unsigned int i = 0; i < VendingMachine::MAXFLAVOURCOUNT; i++){
			cargo[i] = shipment[i];
			shipment[i] = 0;
		}

		printer.print(Printer::BottlingPlant,'P');
		return false;
	}
}


void BottlingPlant::main(){											// loop while not closing
	printer.print(Printer::BottlingPlant,'S');

	// loop until destructor is called
	// create a shipment, then wait for either destructor to be called or a getshipment to be called
	while(true){
		yield(timeBetweenShipments);								// yield time between shipments

		unsigned int bottleCount=0;
		for(unsigned int i = 0; i < VendingMachine::MAXFLAVOURCOUNT; i++){	// generate bottles for next shipment
			shipment[i] = rng(0, maxStockPerFlavour);
			bottleCount += shipment[i];
		}

		printer.print(Printer::BottlingPlant,'G', bottleCount);

		_Accept(~BottlingPlant){
			isClosing = true; 
			break;
		}
		or
		_Accept(getShipment){
		}
	}
	
	_Accept(getShipment){											// wait until truck gets last shipment
	}

	printer.print(Printer::BottlingPlant,'F');
}
