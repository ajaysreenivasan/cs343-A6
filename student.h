#ifndef STUDENT_H
#define STUDENT_H

#include "MPRNG.h"

#include "printer.h"
#include "nameServer.h"
#include "watCardOffice.h"
#include "watcard.h"
#include "vendingMachine.h"

extern MPRNG rng;

_Task Student {
public:
	Student(Printer& prt, NameServer& nameServer, WATCardOffice& cardOffice, unsigned int id,
		unsigned int maxPurchases);

private:
	void main();

private:
	Printer& printer;
	NameServer& nameServer;
	WATCardOffice& cardOffice;
	unsigned int id;
	unsigned int maxPurchases;
	unsigned int numToPurchase;
	WATCard::FWATCard fWATCard;
	VendingMachine::Flavours favouriteFlavour;
};

#endif

// comment