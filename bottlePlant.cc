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

	this->shippingTruck = new Truck(printer, nameServer, *this,
		numVendingMachines, maxStockPerFlavour);
}

BottlingPlant::~BottlingPlant(){
	delete shippingTruck;
}

// clear what has been produced, and set the cargo to what's been produced
// clear own cargo
// before that, check if the plant's closing down (because of students?

// check if plant's clsoing down <- this happens when main destroys plant
// yes -> truck fuck off
// else -> fill truck
bool BottlingPlant::getShipment(unsigned int cargo[]){
	return false;
}

void BottlingPlant::main(){
	_Accept(~BottlingPlant){
		bool flag = true; // ????
	}
	or
		_Accept(getShipment){
			// check if flag is true, if yes, destroy the truck ?? 
	}
}

// makes fucking things (four flavours of sodar)
// you have you have you have your own cargo like your own production line huh
// yeah so you have your own production line an then you make shit
// and after you've made shit you accept a trucks w/e the fuck's function it was
// the one that takes cargo and shit
// and you keep looping that
// uh when you take the uh when you accept the function that takes cargo, you also gotta accept the destructor
// and when you get y