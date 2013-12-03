#ifndef PARENT_H
#define PARENT_H

#include "MPRNG.h"

#include "printer.h"
#include "bank.h"
#include "truck.h"

extern MPRNG rng;

// parent declaration
_Task Parent {
public:
	Parent(Printer& prt, Bank& bank, unsigned int numStudents, unsigned int parentalDelay); // constructor

private:
	void main();

private:
	Printer& printer;
	Bank& bank;
	unsigned int numStudents;			// # of students 
	unsigned int parentalDelay;			// delay between parent deposits of currency
};

#endif