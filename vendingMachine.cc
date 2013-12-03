#include "vendingMachine.h"
#include "printer.h"
#include <iostream>

// constructor
// assigns passed in values to appropriate variables
// initializes member variables
VendingMachine::VendingMachine(Printer& prt, NameServer& nameServer, unsigned int id, unsigned int sodaCost,
							   unsigned int maxStockPerFlavour):
	printer(prt),
	nameServer(nameServer)
{
	this->id = id;
	this->sodaCost = sodaCost;

	this->sodaInventory = new unsigned int[VendingMachine::MAXFLAVOURCOUNT];					//initialize soda inventory
	for(unsigned int i = 0; i < VendingMachine::MAXFLAVOURCOUNT; i++){
		sodaInventory[i] = 0;
	}
}

// destructor
// delete soda inventory
VendingMachine::~VendingMachine(){
	delete[] sodaInventory;
}


VendingMachine::Status VendingMachine::buy(Flavours flavour, WATCard& card){
	if(sodaInventory[flavour] > 0){													// check if flavour is in in stock 
		if(card.getBalance() >= sodaCost){											// and if card has enough balance
			sodaInventory[flavour] -= 1;											// decrement from machine's soda inventory
			card.withdraw(sodaCost);
																					// buy and withdraw cost of bottle from card
			printer.print(Printer::Vending,id,'B',
				flavour,sodaInventory[flavour]);

			return VendingMachine::BUY;
		}
		else{																		// if not enough funds return FUNDS
			return VendingMachine::FUNDS;
		}
	}
	else{
		return VendingMachine::STOCK;												// if none in stock return STOCK
	}
}

// returns the machine's current soda inventory
unsigned int* VendingMachine::inventory(){
	printer.print(Printer::Vending,id,'r');
	return sodaInventory;
}

// signals that the machine is restocked
void VendingMachine::restocked(){
	printer.print(Printer::Vending,id,'R');
}

// returns cost/soda
_Nomutex unsigned int VendingMachine::cost(){
	return sodaCost;
}

// returns machine's id
_Nomutex unsigned int VendingMachine::getId(){
	return id;
}

// main
// registers itself w/ the nameserver
// only accepts a buy or inventory
// if inventory is accepted, all actions will be blocked until restocked is called (mutual exclusion implemented this way)
// breaks when destructor is called
void VendingMachine::main(){
	printer.print(Printer::Vending,id,'S',sodaCost);

	nameServer.VMregister(this);																	//main loop until destructor calledd
	while(true){
		_Accept(buy){

		}
		or
		_Accept(inventory){
			_Accept(restocked){
			
			}
		}
		or
		_Accept(~VendingMachine){
			break;
		}
	}
	printer.print(Printer::Vending,id,'F');
}