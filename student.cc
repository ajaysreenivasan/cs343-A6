#include "student.h"
#include "vendingMachine.h"
#include "watCardOffice.h"
#include <iostream>

using namespace std;

Student::Student(Printer& prt, NameServer& nameServer, WATCardOffice& cardOffice, unsigned int id,
				 unsigned int maxPurchases):
									printer(prt),
									nameServer(nameServer), 
									cardOffice(cardOffice),
									maxPurchases(maxPurchases)
{
	this->id = id;
	numToPurchase = rng(1, maxPurchases); 	//random number bottles to purchase between 1 and maxPurchases			 	
	favouriteFlavour = (VendingMachine::Flavours)rng(3); //random favorite flavour between [0,3]
	
}

void Student::main(){
	printer.print(Printer::Student,id,'S', (int)favouriteFlavour,numToPurchase);
	//this should be a flavour
	bool watCardLost=true;					//set to true to do initial create
	
	while(watCardLost){												//possible that watcard is lost by courier . need to account for this
		try{
			fWATCard = cardOffice.create(id, 5);					//create new watCard for student with 5$
			fWATCard();
			watCardLost=false;
		}
		catch(WATCardOffice::Lost){
			printer.print(Printer::Student,id,'L');
			watCardLost=true;									//new watcard was lost retry creating with 5$
		}
	}
	

	VendingMachine* vmLocation = nameServer.getMachine(id);			//get vending machine location via name server
	printer.print(Printer::Student,id,'V',vmLocation->getId());
	
	bool noYield=false;			//noYield used to tell not needing to yield
	while(numToPurchase > 0){
		//attempt to purchase soda
		//yield random number of times between 1 and 10
		if(!noYield){
			yield(rng(1, 10));
		}
		noYield=false;																//set to false for now to indicate next loop through it will need to yield
		//attempt to buy the soda from machine
		VendingMachine::Status stat= vmLocation->buy(favouriteFlavour, *fWATCard()); 
		//not compiling

		if(stat==VendingMachine::STOCK){
			//get new vending machine if stat == STOCK
			vmLocation=nameServer.getMachine(id);
			printer.print(Printer::Student,id,'V',vmLocation->getId());
		}
		else if(stat==VendingMachine::FUNDS){
		//block while update to funds is made need to account for different cases here
			try{
				fWATCard=cardOffice.transfer(id,vmLocation->cost()+5,fWATCard());
				fWATCard();
			}
			catch(WATCardOffice::Lost){
				printer.print(Printer::Student,id,'L');
				watCardLost=true;												//watcard lost, create new watcard
				while(watCardLost){
					try{
						fWATCard = cardOffice.create(id, 5);					//create new watCard for student with 5$
						fWATCard();
						watCardLost=false;
					}
					catch(WATCardOffice::Lost){
						printer.print(Printer::Student,id,'L');
						watCardLost=true;									//new watcard was lost retry creating with 5$
					}
				}
			}
			noYield=true;													//no yeild to allow student to recall buy without having to yield
		}
		else{	//stat == BUY successfully purchased soda
			numToPurchase--;
			printer.print(Printer::Student,id,'B',fWATCard()->getBalance());
		}
	}//end purchase while loop

	//all soda planned to purchase is purchased terminate
	printer.print(Printer::Student,id,'F');
}

// comment