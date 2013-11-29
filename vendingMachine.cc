#include "vendingMachine.h"
#include "printer.h"

using namespace std;

void VendingMachine::main(){

}

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour ){

}

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card ){
	return VendingMachine::BUY;
}

unsigned int * VendingMachine::inventory(){
	return NULL;
}

void VendingMachine::restocked(){

}

_Nomutex unsigned int VendingMachine::cost(){
	return 0;
}

_Nomutex unsigned int VendingMachine::getId(){
	return 0;
	
}