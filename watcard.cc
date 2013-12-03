#include "watcard.h"

// constructor
// inits card's balance to zero
WATCard::WATCard(){
	this->balance = 0;
}

// deposits the given amount into the watcard
void WATCard::deposit(unsigned int amount){
	this->balance += amount;
}

// withdraws the given amount from the watcard
void WATCard::withdraw(unsigned int amount){
	this->balance -= amount;
}

// returns the watcard's balance
unsigned int WATCard::getBalance(){
	return balance;
}

// private copy constructor (to prevent copying)
WATCard::WATCard(const WATCard&){
}

// private assignment operator (to prevent copying?)
WATCard& WATCard::operator=(const WATCard&){
}