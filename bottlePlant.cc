#include "bottlePlant.h"

// constructor
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
	this->shippingTruck = new Truck(printer, nameServer, *this,		//creating truck
		numVendingMachines, maxStockPerFlavour);
}

BottlingPlant::~BottlingPlant(){									//deconstructor
	delete shipment;
}

bool BottlingPlant::getShipment(unsigned int cargo[]){				//if plant closing down return true
	if(isClosing){
		return true;
	}
	else{															//else copy shipment into the truck and return false
		for(unsigned int i = 0; i < VendingMachine::MAXFLAVOURCOUNT; i++){
			cargo[i] = shipment[i];
			shipment[i] = 0;
		}
		printer.print(Printer::BottlingPlant,'P');
		return false;
	}
}

void BottlingPlant::main(){											//loop while not closing
	printer.print(Printer::BottlingPlant,'S');
	while(true){
		yield(timeBetweenShipments);								//yield time between shipments
		unsigned int bottleCount=0;
		for(unsigned int i = 0; i < VendingMachine::MAXFLAVOURCOUNT; i++){			//ermmm .... how are shipments tied to truck?
			shipment[i] = rng(0, maxStockPerFlavour-1);
			bottleCount+=shipment[i];
		}
		printer.print(Printer::BottlingPlant,'G', bottleCount);

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
	printer.print(Printer::BottlingPlant,'F');
}

// comment
// comment