#ifndef STUDENT_H
#define STUDENT_H

#include "MPRNG.h"

#include "printer.h"
#include "nameServer.h"
#include "watCardOffice.h"
#include "watcard.h"
#include "vendingMachine.h"

extern MPRNG rng;

// declaration of Student
_Task Student {
public:
	// constructor
	Student(Printer& prt, NameServer& nameServer, WATCardOffice& cardOffice, unsigned int id, 
		unsigned int maxPurchases);

private:
	void main();

private:
	Printer& printer;
	NameServer& nameServer;
	WATCardOffice& cardOffice;
	unsigned int id;									// student id
	unsigned int maxPurchases;							// # of sodas student will buy in total
	unsigned int numToPurchase;							// # of sodas student has left to buy
	WATCard::FWATCard fWATCard;							// watcard future
	VendingMachine::Flavours favouriteFlavour;			// student's favourite flavour of soda
};

#endif