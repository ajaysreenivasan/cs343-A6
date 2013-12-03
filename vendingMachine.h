#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

#include "printer.h"
#include "nameServer.h"
#include "watcard.h"

// declaration of VendingMachine
_Task VendingMachine {
public:
	enum Flavours {Smirnoff, Greygoose, Absolut, Belvedere, MAXFLAVOURCOUNT};    // flavours of soda (YOU DEFINE)
	enum Status {BUY, STOCK, FUNDS};									// purchase status: successful buy, out of stock, insufficient funds

public:
	VendingMachine(Printer& prt, NameServer& nameServer, unsigned int id, unsigned int sodaCost, 
		unsigned int maxStockPerFlavour);				// constructor
	~VendingMachine();									// destructor
	Status buy(Flavours flavour, WATCard& card);		// called by student to buy a flavour
	unsigned int* inventory();							// returns inventory of machine
	void restocked();									// alerts machine that it has been restocked
	_Nomutex unsigned int cost();						// returns cost/soda
	_Nomutex unsigned int getId();						// returns machine's id

private:
	void main();

private:
	Printer& printer;
	NameServer& nameServer;
	unsigned int id;									// machine's id
	unsigned int sodaCost;								// cost per soda
	unsigned int* sodaInventory;						// inventory of soda in machine
};

#endif