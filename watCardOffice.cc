#include "watCardOffice.h"
#include "watcard.h"

void WATCardOffice::main(){

}

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ){

}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ){
	return NULL;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ){
	return NULL;
}

WATCardOffice::Job *WATCardOffice::requestWork(){
	return NULL;
}