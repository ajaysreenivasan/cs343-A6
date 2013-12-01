#include "watcard.h"

// constructor
WATCard::WATCard(){
	this->balance = 0;
}

void WATCard::deposit(unsigned int amount){
	this->balance += amount;
}

void WATCard::withdraw(unsigned int amount){
	this->balance -= amount;
}

unsigned int WATCard::getBalance(){
	return balance;
}

// private copy constructor (to prevent copying)
WATCard::WATCard(const WATCard&){
}

// private assignment operator (to prevent copying?)
WATCard& WATCard::operator=(const WATCard&){
}