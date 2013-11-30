#ifndef PARENT_H
#define PARENT_H

#include "printer.h"
#include "bank.h"

extern MPRNG rng;

_Task Parent {
public:
	Parent(Printer& prt, Bank& bank, unsigned int numStudents, unsigned int parentalDelay);

private:
	void main();

private:
	Printer& printer;
	Bank& bank;
	unsigned int numStudents;
	unsigned int parentalDelay;
};

#endif