#ifndef WATCARD_H
#define WATCARD_H

#include <uC++.h>
#include <uFuture.h>

class WATCard {
public:
	WATCard();
	typedef Future_ISM<WATCard*> FWATCard; // future watcard pointer
	void deposit(unsigned int amount);
	void withdraw(unsigned int amount);
	unsigned int getBalance();

private:
	WATCard(const WATCard&);            // prevent copying
	WATCard& operator=(const WATCard&);

private:
	unsigned int balance;
};

#endif

//// private copy constructor (to prevent copying)
//WATCard::WATCard(const WATCard&){
//
//}
//
//// private assignment operator (to prevent copying?)
//WATCard& WATCard::operator=(const WATCard&){
//
//}