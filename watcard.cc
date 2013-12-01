#include "watcard.h"

using namespace std;

// constructor
WATCard::WATCard(){

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



// comment