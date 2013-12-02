#include "vendingMachine.h"
#include "printer.h"
#include <iostream>

using namespace std;

VendingMachine::VendingMachine(Printer& prt, NameServer& nameServer, unsigned int id, unsigned int sodaCost,
							   unsigned int maxStockPerFlavour):
printer(prt),
	nameServer(nameServer)
{
	this->id = id;
	this->sodaCost = sodaCost;

	this->sodaInventory = new unsigned int[VendingMachine::MAXFLAVOURCOUNT];						//initialize soda inventory
	for(unsigned int i = 0; i < VendingMachine::MAXFLAVOURCOUNT; i++){
		sodaInventory[i] = 0;
	}
}

VendingMachine::~VendingMachine(){
	delete[] sodaInventory;
}

VendingMachine::Status VendingMachine::buy(Flavours flavour, WATCard& card){
	if(sodaInventory[flavour] > 0){																	//flavour is in in stock 
		if(card.getBalance() >= sodaCost){															// and if card has enough balance
			sodaInventory[flavour] -= 1;
			card.withdraw(sodaCost);
																									//buy and withdraw cost of bottle from card
			printer.print(Printer::Vending,id,'B',
				flavour,sodaInventory[flavour]);

			return VendingMachine::BUY;
		}
		else{																						//if not enough funds return FUNDS
			return VendingMachine::FUNDS;
		}
	}
	else{
		return VendingMachine::STOCK;																//if none in stock return STOCK
	}
}

unsigned int* VendingMachine::inventory(){
	printer.print(Printer::Vending,id,'r');
	return sodaInventory;
}

void VendingMachine::restocked(){
	printer.print(Printer::Vending,id,'R');
}

_Nomutex unsigned int VendingMachine::cost(){
	return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId(){
	return id;
}

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