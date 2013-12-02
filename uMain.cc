#include <uC++.h>
#include <iostream>
#include <vector>
#include "MPRNG.h"
#include "printer.h"
#include <cstdlib>
#include "config.h"
#include "bank.h"
#include "parent.h"
#include "watCardOffice.h"
#include "nameServer.h"
#include "vendingMachine.h"
#include "bottlePlant.h"
#include "student.h"

using namespace std;

MPRNG rng;

void uMain::main(){
	char * inputFile = "soda.config";														//defaul param values
	unsigned int seed=getpid();

	cout << "hey" << endl;

	vector<VendingMachine*> vendingMachines;												//containers for holding VendingMachine and Student tasks
	vector<Student*> students;

	if(argc>=2)
		inputFile=argv[1];
	if(argc>=3)
		seed=atoi(argv[2]);

	cout << "hey2" << endl;																					//assignment says no error check required on input

	rng.seed(seed);

	ConfigParms cp;																			//process confiigFile
	processConfigFile(inputFile,cp);
	cout << "hey4" << endl;																			//create specified tasks in correct order
	Printer* printer = new Printer(cp.numStudents,cp.numVendingMachines,cp.numCouriers);
	cout << "hey6" << endl;
	cout << cp.numStudents << endl;
	Bank* bank = new Bank(cp.numStudents);
	cout << "hey7" << endl;
	Parent* parent = new Parent(*printer, *bank, cp.numStudents, cp.parentalDelay);
	cout << "hey66345" << endl;
	WATCardOffice* cardOffice= new WATCardOffice(*printer, *bank, cp.numCouriers);
	cout << "hey535" << endl;
	NameServer* nameServer = new NameServer(*printer, cp.numVendingMachines,cp.numStudents);
	cout << "hey2323" << endl;

	for(unsigned int i = 0; i < cp.numVendingMachines; i++){
		VendingMachine* newVendingMachine = new VendingMachine(*printer,*nameServer,i,
			cp.sodaCost,cp.maxStockPerFlavour);
			cout << "heyblargh " << i << endl;
		vendingMachines.push_back(newVendingMachine);
	}
		cout << "asdfasdfasdf " << endl;
	BottlingPlant* bottlePlant = new BottlingPlant(*printer, *nameServer,cp.numVendingMachines,
		cp.maxShippedPerFlavour, cp.maxStockPerFlavour,
		cp.timeBetweenShipments);
			cout << "agararagaweg " << endl;
	for(unsigned int i =0; i< cp.numStudents; i++){
		Student* tempStudent = new Student(*printer, *nameServer, *cardOffice,i,cp.maxPurchases);
		students.push_back(tempStudent);
	}
			cout << "hergaderg " << endl;


	while(!students.empty()){																//program ends when students finish so delete them first
		delete students.back();
		students.pop_back();
	}

	delete bottlePlant;																		//delete bottle next to allow last shipment to finish

	while(!vendingMachines.empty()){														//then delete vending machines
		delete vendingMachines.back();
		vendingMachines.pop_back();
	}

	delete nameServer;																		//then delete rest
	delete cardOffice;
	delete parent;
	delete bank;
	delete printer;

	cout<<"***********************\n";
	return;
}

// comment