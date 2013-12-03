#include "watCardOffice.h"
#include "watcard.h"

// constructor
// inits vars to appropriate values if given
WATCardOffice::WATCardOffice(Printer& prt, Bank& bank, unsigned int numCouriers):
	printer(prt),
	bank(bank)
{
	this->numCouriers = numCouriers;

	courierList = new Courier*[numCouriers];											// initialize couriers
	for(unsigned int i = 0; i < numCouriers; i++){
		courierList[i] = new Courier(bank, *this, printer,i);
	}

	isClosing = false;
}

// destructor
// deletes couriers and the courier list
WATCardOffice::~WATCardOffice(){
	for(unsigned int i = 0; i < numCouriers; i++){											//delete couriers
		delete courierList[i];
	}

	delete[] courierList;
}

// creates a new watcard for a student with a given id and amount
WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount){				// create future watcard
	Job* newJob = new Job(sid, 0, amount);													// create a new job and push it into the jobqueue	
	jobQueue.push(newJob);

	printer.print(Printer::WATCardOffice,'C',sid,amount);

	jobAvailableCondition.signal();															// signal that a job is now available

	return newJob->result;
}

// transfers balance from old watcard to new card
WATCard::FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard* card){	//tranfer  money onto input card
	unsigned int cardBalance = card->getBalance();											// retrieves balance from old card										
	Job* newJob = new Job(sid, cardBalance, amount);										// creates new job and pushes onto queue
	jobQueue.push(newJob);

	printer.print(Printer::WATCardOffice,'T',sid,amount);

	jobAvailableCondition.signal();															// signals that a job is available

	delete card;																			// deletes old card
	return newJob->result;
}

// requests work from the office
WATCardOffice::Job* WATCardOffice::requestWork(){											// couriers request work and unblock when work available for them
	if(jobQueue.size() == 0){
		jobAvailableCondition.wait();														// blocks if no work to be done
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
		or																					// otherwise, accept create, transfer and requestWork calls
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

//Job holds information for courier tasks
// constructor, inits values to given arguments
WATCardOffice::Job::Job(unsigned int sid, unsigned int cardBalance, unsigned int withdrawalAmount) {	
	this->sid = sid;
	this->cardBalance = cardBalance;
	this->withdrawalAmount = withdrawalAmount;
}

// courier constructor
WATCardOffice::Courier::Courier(Bank& bank, WATCardOffice& cardOffice,Printer& prt,unsigned int id):
	bank(bank),
	cardOffice(cardOffice),
	printer(prt)
{
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
		
		bank.withdraw(newJob->sid, newJob->withdrawalAmount);						//withdraw money from back to place on new watcard
		
		WATCard* newWATCard = new WATCard();
		newWATCard->deposit(newJob->withdrawalAmount);
		newWATCard->deposit(newJob->cardBalance);

		unsigned int cardDropChance = rng(0, 5);

		if(cardDropChance > 0){														// check if courier loses watcard and place value in future
			newJob->result.delivery(newWATCard);									// if courier hasn't lost the card, deliver it
		}
		else{
			newJob->result.exception(new WATCardOffice::Lost);						// throw an exception if the courier has lost the card
			delete newWATCard;														// delete the card to "lose it"
		}
		printer.print(Printer::Courier,id,'T',newJob->sid,newJob->withdrawalAmount);
		
		delete newJob;																// delete the job when it's done
	}

	printer.print(Printer::Courier,id,'F');
}