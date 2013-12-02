#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H

#include <queue>

#include "printer.h"
#include "bank.h"
#include "watcard.h"

#include "MPRNG.h"

extern MPRNG rng;

_Task WATCardOffice {
private:
	struct Job;

public:
	_Event Lost {};                        // uC++ exception type, like "struct"
	WATCardOffice(Printer& prt, Bank &bank, unsigned int numCouriers);
	~WATCardOffice();
	WATCard::FWATCard create(unsigned int sid, unsigned int amount);
	WATCard::FWATCard transfer(unsigned int sid, unsigned int amount, WATCard* card);
	Job* requestWork();

private:
	struct Job {                           // marshalled arguments and return future
		Job(unsigned int sid, unsigned int cardBalance, unsigned int withdrawalAmount);

		WATCard::FWATCard result;          // return future
		unsigned int sid;
		unsigned int cardBalance;
		unsigned int withdrawalAmount;
	};
	_Task Courier {							// communicates with bank
	public:
		Courier(Bank& bank, WATCardOffice& cardOffice);
	private:
		void main();

		Bank& bank;
		WATCardOffice& cardOffice;
	};					 

private:
	void main();

private:
	Printer& printer;
	Bank& bank;
	WATCard* card;
	unsigned int numCouriers;
	Courier** courierList;
	std::queue<Job*> jobQueue;
	uCondition jobAvailableCondition;
};

#endif

// comment