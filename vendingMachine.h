#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

#include "printer.h"
#include "nameServer.h"
#include "watcard.h"

_Task VendingMachine {
public:
	enum Flavours {Cola, DuffBeer, RainbowCider, FizzyLiftingDrink};    // flavours of soda (YOU DEFINE)
	enum Status {BUY, STOCK, FUNDS};									// purchase status: successful buy, out of stock, insufficient funds

public:
	VendingMachine(Printer& prt, NameServer& nameServer, unsigned int id, unsigned int sodaCost,
		unsigned int maxStockPerFlavour);
	Status buy(Flavours flavour, WATCard& card);
	unsigned int* inventory();
	void restocked();
	_Nomutex unsigned int cost();
	_Nomutex unsigned int getId();

private:
	void main();

private:
	Printer& printer;
	NameServer& nameServer;
	unsigned int id;
	unsigned int sodaCost;
};

#endif