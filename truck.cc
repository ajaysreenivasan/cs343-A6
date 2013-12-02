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

	this->cargo = new unsigned int[VendingMachine::MAXFLAVOURCOUNT];
	this->hasCargo = false;
}

Truck::~Truck(){
	delete[] cargo;
}

																				// main method
void Truck::main(){
	printer.print(Printer::Truck,'S');
	while(true){																//loop while plant isn't closing
		yield(10);
		if(plant.getShipment(cargo)){											//obtaint next shipment to deliver
			break;	
		}
		hasCargo = true;
		printer.print(Printer::Truck,'P',getCargoCount());

		VendingMachine** vendingMachineList = nameServer.getMachineList();		//get list of vending machines to deliver to
		VendingMachine* vendingMachine;
		unsigned int* vendingMachineInventory;

		for(unsigned int i = 0; i < numVendingMachines; i++){					//deliver to vending machines while there is cargo and vendingmachines to deliver to
			if(!hasCargo)
				break;

			vendingMachine = vendingMachineList[i];
			vendingMachineInventory = vendingMachine->inventory();

			unsigned int restockRequirement=0;
			unsigned int unfilledBottles=0;
			printer.print(Printer::Truck,'d',i,getCargoCount());
			for(unsigned int i = 0; i < VendingMachine::MAXFLAVOURCOUNT; i++){	//restock the correct amount of bottles for a given flavour at current vending machine index
				if(vendingMachineInventory[i] < maxStockPerFlavour){
					restockRequirement = maxStockPerFlavour - vendingMachineInventory[i];
					if(cargo[i] >= restockRequirement){
						vendingMachineInventory[i] += restockRequirement;
						cargo[i]-=restockRequirement;
					}
					else
						vendingMachineInventory[i] += cargo[i];
						unfilledBottles+=restockRequirement-cargo[i];
						cargo[i]=0;
				}
			}
			printer.print(Printer::Truck,'U',i,unfilledBottles);

			vendingMachine->restocked();										//finish restocking current vending machine
			
			printer.print(Printer::Truck,'D',i,getCargoCount());

			checkCargo();
		}		
	}
	printer.print(Printer::Truck,'F');
}

unsigned int Truck::getCargoCount(){											//printing helper function
	int stockCount = 0;
	for(unsigned int i = 0; i < VendingMachine::MAXFLAVOURCOUNT; i++){
		stockCount += cargo[i];
	}
	return stockCount;
}

void Truck::checkCargo(){
	int stockCount = getCargoCount();
	if(stockCount == 0)
		this->hasCargo = false;
	else
		this->hasCargo = true;
}