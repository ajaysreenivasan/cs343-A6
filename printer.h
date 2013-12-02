#ifndef PRINTER_H
#define PRINTER_H

#include <uC++.h>
#include <string>
#include <vector>

_Monitor Printer {
public:
	enum Kind {Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier};

public:
	Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers);
	void print(Kind kind, char state);
	void print(Kind kind, char state, int value1);
	void print(Kind kind, char state, int value1, int value2);
	void print(Kind kind, unsigned int lid, char state);
	void print(Kind kind, unsigned int lid, char state, int value1);
	void print(Kind kind, unsigned int lid, char state, int value1, int value2);

private:
	void flushLine();
	void updateBuffer(unsigned int index, std::string newValue);
	void finish(unsigned int index);
	unsigned int getIndex(Kind kind);
	unsigned int getIndex(Kind kind, unsigned int lid);
	void printDebug(unsigned int i);

private:
	unsigned int numStudents;
	unsigned int numVendingMachines;
	unsigned int numCouriers;
	Printer::Kind kind;
	std::vector<std::string> buffer;
};

#endif

// comment