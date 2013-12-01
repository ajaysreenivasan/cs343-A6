#ifndef PARENT_H
#define PARENT_H

#include "MPRNG.h"

#include "printer.h"
#include "bank.h"
#include "truck.h"

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

// comment