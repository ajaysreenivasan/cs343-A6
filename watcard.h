#ifndef WATCARD_H
#define WATCARD_H

#include <uC++.h>
#include <uFuture.h>

// declaration of WATCard
class WATCard {
public:
	WATCard();								// constructor
	typedef Future_ISM<WATCard*> FWATCard; // future watcard pointer
	void deposit(unsigned int amount);		// deposit money to a watcard from bank
	void withdraw(unsigned int amount);		// withdraw money from watcard
	unsigned int getBalance();				// return balance of this watcard

private:
	WATCard(const WATCard&);            // prevent copying
	WATCard& operator=(const WATCard&);

private:
	unsigned int balance;
};

#endif