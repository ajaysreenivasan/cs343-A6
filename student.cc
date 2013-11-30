#include "student.h"
#include "MPRNG.h"
#include "vendingMachine.h"

using namespace std;

extern MPRNG m;

void Student::main(){
	
	int favFlav = m(3);					 	//random favorite flavour between [0,3]
	//this should be a flavour 

	wco->create(id,5);					//create new watCard for student with 5$
	//possible that watcard is lost by courier -> need to account for this

	VendingMachine * vmLocation=ns->getMachine(id);			//get vending machine location via name server

	while(numToPurchase>0){

	}

}

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int _id,
             unsigned int maxPurchases ){
	p=&prt;
	ns=&nameServer;
	wco=&cardOffice;
	id=_id;
	numToPurchase=m(1,maxPurchases); 	//random number bottles to purchase between 1 and maxPurchases
}