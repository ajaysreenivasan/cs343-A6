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

	this->sodaInventory = new unsigned int[VendingMachine::MAXFLAVOURCOUNT];
	for(unsigned int i = 0; i < VendingMachine::MAXFLAVOURCOUNT; i++){
		sodaInventory[i] = 0;
	}

	cout << "GARBAGE" << endl;

	nameServer.VMregister(this);

	
	cout << "TRASH" << endl;
}

VendingMachine::Status VendingMachine::buy(Flavours flavour, WATCard& card){
	if(sodaInventory[flavour] > 0){
		if(card.getBalance() >= sodaCost){
			sodaInventory[flavour] -= 1;
			card.withdraw(sodaCost);
			return VendingMachine::BUY;
		}
		else{
			return VendingMachine::FUNDS;
		}
	}
	else{
		return VendingMachine::STOCK;
	}
}

unsigned int* VendingMachine::inventory(){
	return sodaInventory;
}

void VendingMachine::restocked(){

}

_Nomutex unsigned int VendingMachine::cost(){
	return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId(){
	return id;
}

void VendingMachine::main(){
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
}