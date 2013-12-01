#include "truck.h"
#include "vendingMachine.h"

// constructor
Truck::Truck(Printer& prt, NameServer& nameServer, BottlingPlant& plant,
			 unsigned int numVendingMachines, unsigned int maxStockPerFlavour):
printer(prt),
	nameServer(nameServer),
	plant(plant)
{
	this->numVendingMachines = numVendingMachines;
	this->maxStockPerFlavour = maxStockPerFlavour;

	this->maxFlavourCount = 4;
	this->cargo = new unsigned int[maxFlavourCount];
	this->hasCargo = false;
}

Truck::~Truck(){
	delete cargo;
}

// main method
void Truck::main(){
	while(true){
		yield(10);
		if(plant.getShipment(cargo)){
			break;	
		}
		hasCargo = true;

		VendingMachine** vendingMachineList = nameServer.getMachineList();
		VendingMachine* vendingMachine;
		unsigned int* vendingMachineInventory;

		for(unsigned int i = 0; i < numVendingMachines; i++){
			if(!hasCargo)
				break;

			vendingMachine = vendingMachineList[i];
			vendingMachineInventory = vendingMachine->inventory();

			unsigned int restockRequirement;

			for(unsigned int i = 0; i < maxFlavourCount; i++){
				if(vendingMachineInventory[i] < maxStockPerFlavour){
					restockRequirement = maxStockPerFlavour - vendingMachineInventory[i];
					if(cargo[i] >= restockRequirement)
						vendingMachineInventory[i] += restockRequirement;
					else
						vendingMachineInventory[i] += cargo[i];
				}
			}
			vendingMachine->restocked();

			checkCargo();
		}		
	}
}

void Truck::checkCargo(){
	int stockCount = 0;
	for(unsigned int i = 0; i < maxFlavourCount; i++){
		stockCount += cargo[i];
	}

	if(stockCount == 0)
		this->hasCargo = false;
	else
		this->hasCargo = true;
}


// comment
// comment