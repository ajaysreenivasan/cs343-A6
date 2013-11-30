#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H

#include "printer.h"
#include "bank.h"
#include "watcard.h"

struct Args{

};

_Task WATCardOffice {
private:
	struct Job;

public:
	_Event Lost {};                        // uC++ exception type, like "struct"
	WATCardOffice(Printer& prt, Bank &bank, unsigned int numCouriers);
	WATCard::FWATCard create(unsigned int sid, unsigned int amount);
	WATCard::FWATCard transfer(unsigned int sid, unsigned int amount, WATCard* card);
	Job* requestWork();

private:
	struct Job {                           // marshalled arguments and return future
		Args args;                         // call arguments (YOU DEFINE "Args")
		WATCard::FWATCard result;          // return future
		Job(Args args) : args(args) {}
	};
	_Task Courier { };                 // communicates with bank

private:
	void main();

private:
	Printer& printer;
	Bank& bank;
	WATCard* card;
	unsigned int numCouriers;
};

#endif