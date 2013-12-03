#include "truck.h"
#include "vendingMachine.h"

// constructor
// assigns passed in values to appropriate member variables
// intializes member variables
Truck::Truck(Printer& prt, NameServer& nameServer, BottlingPlant& plant,
			 unsigned int numVendingMachines, unsigned int maxStockPerFlavour):
	printer(prt),
	nameServer(nameServer),
	plant(plant)
{
	this->numVendingMachines = numVendingMachines;
	this->maxStockPerFlavour = maxStockPerFlavour;

	this->cargo = new unsigned int[VendingMachine::MAXFLAVOURCOUNT];
	this->hasCargo = false;
}

// destructor
// deletes cargo
Truck::~Truck(){
	delete[] cargo;
}

// main method
void Truck::main(){
	printer.print(Printer::Truck,'S');

	while(true){																// loop while plant isn't closing
		yield(10);																// yields for 10
		if(plant.getShipment(cargo)){											// obtain next shipment to deliver
			break;																// break if the plant is closing
		}
		hasCargo = true;
		printer.print(Printer::Truck,'P', getCargoCount());

		VendingMachine** vendingMachineList = nameServer.getMachineList();		// get list of vending machines to deliver to
		VendingMachine* vendingMachine;											
		unsigned int* vendingMachineInventory;

		for(unsigned int i = 0; i < numVendingMachines; i++){					// deliver to vending machines while there is cargo and vendingmachines to deliver to
			if(!hasCargo)														// stop delivering if there's no more cargo left
				break;

			vendingMachine = vendingMachineList[i];
			vendingMachineInventory = vendingMachine->inventory();				// gets inventory of current vending machine

			unsigned int restockRequirement = 0;								// amount required to fully restock machine
			unsigned int unfilledBottles = 0;									// amount of bottles that couldn't be restocked 
			printer.print(Printer::Truck,'d',i,getCargoCount());

			for(unsigned int i = 0; i < VendingMachine::MAXFLAVOURCOUNT; i++){	//restock the correct amount of bottles for a given flavour at current vending machine index
				if(vendingMachineInventory[i] < maxStockPerFlavour){
					restockRequirement = maxStockPerFlavour - vendingMachineInventory[i];
					
					if(cargo[i] >= restockRequirement){							// if there are enough bottles to restock fully, do so
						vendingMachineInventory[i] += restockRequirement;
						cargo[i] -= restockRequirement;
					}
					else{														// otherwise, restock what it can, mark the rest as unfilled
						vendingMachineInventory[i] += cargo[i];
						unfilledBottles += restockRequirement - cargo[i];
						cargo[i] = 0;
					}
				}
			}
			printer.print(Printer::Truck,'U',i,unfilledBottles);

			vendingMachine->restocked();										//finish restocking current vending machine

			printer.print(Printer::Truck,'D',i,getCargoCount());

			checkCargo();														// check if the truck still has cargo
		}		
	}

	printer.print(Printer::Truck,'F');
}

// counts the truck's count
unsigned int Truck::getCargoCount(){											//printing helper function
	int stockCount = 0;
	for(unsigned int i = 0; i < VendingMachine::MAXFLAVOURCOUNT; i++){
		stockCount += cargo[i];
	}
	return stockCount;
}

// checks if the truck has any cargo left
// returns true if it does
// false if it doesn't
void Truck::checkCargo(){
	int stockCount = getCargoCount();
	if(stockCount == 0)
		this->hasCargo = false;
	else
		this->hasCargo = true;
}