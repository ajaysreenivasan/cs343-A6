#ifndef STUDENT_H
#define STUDENT_H

#include "printer.h"
#include "nameServer.h"
#include "watCardOffice.h"
#include "watcard.h"

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
  WATCard::FWATCard fw;
};

#endif