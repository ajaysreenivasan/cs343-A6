#include "student.h"
#include "vendingMachine.h"

Student::Student(Printer& prt, NameServer& nameServer, WATCardOffice& cardOffice, unsigned int id,
				 unsigned int maxPurchases):
printer(prt),
	nameServer(nameServer), 
	cardOffice(cardOffice)
{
	id = id;
	numToPurchase = rng(1, maxPurchases); 	//random number bottles to purchase between 1 and maxPurchases
}

void Student::main(){
	int favFlav = rng(3);					 	//random favorite flavour between [0,3]
	//this should be a flavour 
	fWATCard = cardOffice.create(id, 5);					//create new watCard for student with 5$
	//possible that watcard is lost by courier . need to account for this

	VendingMachine* vmLocation = nameServer.getMachine(id);			//get vending machine location via name server

	while(numToPurchase > 0){
		//attempt to purchase soda
		//yield random number of times between 1 and 10
		yield(rng(1, 10));

		//attempt to buy the soda from machine
		//VendingMachine::Status stat= vmLocation->buy(favFlav, fWATCard); 
		//not compiling

		/*if(stat==VendingMachine::STOCK){
		//get new vending machine if stat == STOCK
		vmLocation=nameServer.getMachine(id);
		}
		else if(stat==VendingMachine::FUNDS){
		//block while update to funds is made need to account for different cases here
		/*try{
		fWATCard=cardOffice.tranameServerfer(id,vmLocation.cost()+5);
		}
		catch(Exception e){ 

		}*/
		/*}
		else{
		//stat == BUY successfully purchased soda
		numToPurchase--;
		}*/
	}

	//all soda planned to purchase is purchased terminate
}

// comment