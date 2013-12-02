#include "watCardOffice.h"
#include "watcard.h"

// constructor
WATCardOffice::WATCardOffice(Printer& prt, Bank& bank, unsigned int numCouriers):
	printer(prt),
	bank(bank)
{
	this->numCouriers = numCouriers;

	courierList = new Courier*[numCouriers];
	for(unsigned int i = 0; i < numCouriers; i++){
		courierList[i] = new Courier(bank, *this, printer);
	}

}

WATCardOffice::~WATCardOffice(){
	for(unsigned int i = 0; i < numCouriers; i++){
		delete courierList[i];
	}
	delete[] courierList;
}

WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount){
	Job* newJob = new Job(sid, 0, amount);
	jobQueue.push(newJob);
	printer.print(Printer::WATCardOffice,'C',sid,amount);
	jobAvailableCondition.signal();

	return newJob->result;
}

WATCard::FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard* card){
	unsigned int cardBalance = card->getBalance();
	Job* newJob = new Job(sid, cardBalance, amount);
	jobQueue.push(newJob);
	printer.print(Printer::WATCardOffice,'T',sid,amount);
	jobAvailableCondition.signal();

	return newJob->result;
}

WATCardOffice::Job* WATCardOffice::requestWork(){
	if(jobQueue.size() == 0){
		jobAvailableCondition.wait();
	}

	Job* job = jobQueue.front();
	jobQueue.pop();
	printer.print(Printer::WATCardOffice,'W');
	return job;
}

void WATCardOffice::main(){
	printer.print(Printer::WATCardOffice,'S');
	while(true){
		_Accept(~WATCardOffice){
			for(unsigned int i = 0; i < numCouriers; i++){
				jobAvailableCondition.signal();
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

WATCardOffice::Job::Job(unsigned int sid, unsigned int cardBalance, unsigned int withdrawalAmount) {
	this->sid = sid;
	this->cardBalance = cardBalance;
	this->withdrawalAmount = withdrawalAmount;
}

WATCardOffice::Courier::Courier(Bank& bank, WATCardOffice& cardOffice,Printer& prt):
bank(bank),
cardOffice(cardOffice),
printer(prt){
	
}

void WATCardOffice::Courier::main(){
	printer.print(Printer::Courier,'S');
	while(true){
		Job* newJob = cardOffice.requestWork();
	
		if(newJob == NULL){
			break;
		}
		printer.print(Printer::Courier,'t',newJob->sid,newJob->withdrawalAmount);
		bank.withdraw(newJob->sid, newJob->withdrawalAmount);
		
		WATCard* newWATCard = new WATCard();
		newWATCard->deposit(newJob->withdrawalAmount);
		newWATCard->deposit(newJob->cardBalance);

		unsigned int cardDropChance = rng(0, 5);

		if(cardDropChance > 0){
			newJob->result.delivery(newWATCard);
		}
		else{
			newJob->result.exception(new WATCardOffice::Lost);
		}
		printer.print(Printer::Courier,'T',newJob->sid,newJob->withdrawalAmount);
		delete newJob;
	}
	printer.print(Printer::Courier,'F');
}