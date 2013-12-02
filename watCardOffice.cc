#include "watCardOffice.h"
#include "watcard.h"
#include <iostream>

using namespace std;
// constructor
WATCardOffice::WATCardOffice(Printer& prt, Bank& bank, unsigned int numCouriers):
	printer(prt),
	bank(bank)
{
	this->numCouriers = numCouriers;

	courierList = new Courier*[numCouriers];												//initialize couriers
	for(unsigned int i = 0; i < numCouriers; i++){
		courierList[i] = new Courier(bank, *this, printer,i);
	}
	isClosing=false;

}

WATCardOffice::~WATCardOffice(){
	for(unsigned int i = 0; i < numCouriers; i++){											//delete couriers
		delete courierList[i];
	}
	delete[] courierList;
}

WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount){				//create future watcard
	Job* newJob = new Job(sid, 0, amount);
	jobQueue.push(newJob);
	printer.print(Printer::WATCardOffice,'C',sid,amount);
	jobAvailableCondition.signal();

	return newJob->result;
}

WATCard::FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard* card){	//tranfer  money onto input card
	unsigned int cardBalance = card->getBalance();
	Job* newJob = new Job(sid, cardBalance, amount);
	jobQueue.push(newJob);
	printer.print(Printer::WATCardOffice,'T',sid,amount);
	jobAvailableCondition.signal();
	delete card;
	return newJob->result;
}

WATCardOffice::Job* WATCardOffice::requestWork(){											//couriers request work and unblock when work available for them
	if(jobQueue.size() == 0){
		jobAvailableCondition.wait();
		if(isClosing){
			return NULL;
		}
	}

	Job* job = jobQueue.front();
	jobQueue.pop();
	printer.print(Printer::WATCardOffice,'W');
	return job;
}

void WATCardOffice::main(){
	printer.print(Printer::WATCardOffice,'S');
	while(true){																			//loop while destructor not called
		_Accept(~WATCardOffice){
			isClosing=true;
			for(unsigned int i = 0; i < numCouriers; i++){									//if destructor called delete couriers prior to office
				jobAvailableCondition.signalBlock();
			}
			break;
		}
		or
		_Accept(create){
		}
		or
		_Accept(transfer){
		}
		or
		_Accept(requestWork){
		}
	}
	printer.print(Printer::WATCardOffice,'F');
}

WATCardOffice::Job::Job(unsigned int sid, unsigned int cardBalance, unsigned int withdrawalAmount) {	//Job holds information for courier tasks
	this->sid = sid;
	this->cardBalance = cardBalance;
	this->withdrawalAmount = withdrawalAmount;
}

WATCardOffice::Courier::Courier(Bank& bank, WATCardOffice& cardOffice,Printer& prt,unsigned int id):
bank(bank),
cardOffice(cardOffice),
printer(prt){
	this->id=id;
}

void WATCardOffice::Courier::main(){
	printer.print(Printer::Courier,id,'S');
	while(true){																						//courier main loop until office is closing
		Job* newJob = cardOffice.requestWork();															//request work from office
	
		if(newJob == NULL){
			break;
		}
		printer.print(Printer::Courier,id,'t',newJob->sid,newJob->withdrawalAmount);
		bank.withdraw(newJob->sid, newJob->withdrawalAmount);
																										//withdraw money from back to place on new watcard
		WATCard* newWATCard = new WATCard();
		newWATCard->deposit(newJob->withdrawalAmount);
		newWATCard->deposit(newJob->cardBalance);

		unsigned int cardDropChance = rng(0, 5);

		if(cardDropChance > 0){																			//check if courier loses watcard and place value in future
			newJob->result.delivery(newWATCard);
		}
		else{
			newJob->result.exception(new WATCardOffice::Lost);
			delete newWATCard;
		}
		printer.print(Printer::Courier,id,'T',newJob->sid,newJob->withdrawalAmount);
		delete newJob;
	}
	printer.print(Printer::Courier,id,'F');
}