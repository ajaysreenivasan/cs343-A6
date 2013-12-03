#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H

#include <queue>

#include "printer.h"
#include "bank.h"
#include "watcard.h"

#include "MPRNG.h"

extern MPRNG rng;

// watcardoffice declaration 
_Task WATCardOffice {
private:
	struct Job;

public:
	_Event Lost {};                        // uC++ exception type, like "struct"
	WATCardOffice(Printer& prt, Bank &bank, unsigned int numCouriers);		// constructor
	~WATCardOffice();														// destructor
	WATCard::FWATCard create(unsigned int sid, unsigned int amount);		// create a watcard
	WATCard::FWATCard transfer(unsigned int sid, unsigned int amount, WATCard* card);	// transfer funds from an old card to new card
	Job* requestWork();

private:
	struct Job {                           // marshalled arguments and return future
		Job(unsigned int sid, unsigned int cardBalance, unsigned int withdrawalAmount);

		WATCard::FWATCard result;          // return future
		unsigned int sid;					// student id
		unsigned int cardBalance;			// balance on card
		unsigned int withdrawalAmount;		// amount to withdraw from bank
	};
	_Task Courier {							// communicates with bank
	public:
		Courier(Bank& bank, WATCardOffice& cardOffice, Printer& printer,unsigned int id);
	private:
		void main();

		Bank& bank;
		WATCardOffice& cardOffice;
		Printer& printer;
		unsigned int id;				// student id
	};					 

private:
	void main();

private:
	Printer& printer;
	Bank& bank;
	WATCard* card;
	unsigned int numCouriers;				// # of couriers
	Courier** courierList;					// tracks the couriers
	std::queue<Job*> jobQueue;				// queues up jobs
	uCondition jobAvailableCondition;		// blocks unless a job is available
	bool isClosing;							// tracks if office is closing
};

#endif