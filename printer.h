#ifndef PRINTER_H
#define PRINTER_H

#include <uC++.h>

_Monitor Printer {
public:
	enum Kind {Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier};

public:
	Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers);
	~Printer();
	void print(Kind kind, char state);
	void print(Kind kind, char state, int value1);
	void print(Kind kind, char state, int value1, int value2);
	void print(Kind kind, unsigned int lid, char state);
	void print(Kind kind, unsigned int lid, char state, int value1);
	void print(Kind kind, unsigned int lid, char state, int value1, int value2);

private:
	void flushLine();
	void updateBuffer(unsigned int index, char state);
	void updateBuffer(unsigned int index, char state, int value1);
	void updateBuffer(unsigned int index, char state, int value1, int value2);
	void finish(unsigned int index);
	unsigned int getIndex(Kind kind);
	unsigned int getIndex(Kind kind, unsigned int lid);
	void printDebug(unsigned int i);

private:
	unsigned int numStudents;
	unsigned int numVendingMachines;
	unsigned int numCouriers;
	Printer::Kind kind;
	char* stateBuffer;
	int* value1Buffer;
	int* value2Buffer;
	unsigned int size;
};

#endif

// comment