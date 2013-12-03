#include "printer.h"
#include <iostream>

using namespace std;

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ){	//constructor
	this->numStudents = numStudents;																		//set member variables
	this->numVendingMachines = numVendingMachines;
	this->numCouriers = numCouriers;
	int idCounter =0;

	this->size=numStudents+numVendingMachines+numCouriers+5;												//allocate mem for buffers
	stateBuffer = new char[size];
	value1Buffer= new int[size];
	value2Buffer=new int[size];

	for(unsigned int i =0;i<size;i++){																		//generate initial output and initial buffer values
		if(i==0){
			cout<<"Parent";
		}
		else if(i==1){
			cout<<"WATOff";
		}
		else if(i==2){
			cout<<"Names";
		}
		else if(i==3){
			cout<<"Truck";
		}
		else if(i==4){
			cout<<"Plant";
		}
		else if(i<5+numStudents){
			cout<<"Stud"<<idCounter++;
		}
		else if(i<5+numVendingMachines+numStudents){
			cout<<"Mach"<<(idCounter++)-numStudents;
		}
		else if(i<5+numVendingMachines+numStudents+numCouriers){
			cout<<"Cour"<<(idCounter++)-numStudents-numVendingMachines;
		}
		stateBuffer[i]='%';
		value1Buffer[i]=-1;
		value2Buffer[i]=-1;
		cout<<"\t";
	}
	cout<<endl;
	for(unsigned int i =0;i<size;i++){
		cout<<"*******\t";
	}
	cout<<endl;
}

Printer::~Printer(){																						//deconstructor delete buffers
	delete[] stateBuffer;
	delete[] value1Buffer;
	delete[] value2Buffer;
	cout<<"***********************\n";
}

/*void Printer::printDebug(unsigned int i){																	//debug method used to determine what task is calling print
cout<<i<<endl;
if(i==0){
cout<<"Parent";
}
else if(i==1){
cout<<"WATOff";
}
else if(i==2){
cout<<"Names";
}
else if(i==3){
cout<<"Truck";
}
else if(i==4){
cout<<"Plant";
}
else if(i>=5 && i<5+numStudents){
cout<<"Stud"<<i-5;
}
else if(i>=5+numStudents && i<5+numVendingMachines+numStudents){
cout<<"Mach"<<i-5-numStudents;
}
else if(i>=5+numVendingMachines+numStudents){
cout<<"Cour"<<i-5-numStudents-numVendingMachines;
}
cout<<endl;
}*/

//Get the buffer index of kinds Parent, WATCardOffice, NameServer, Truck, BottlingPlant
unsigned int Printer::getIndex(Kind kind){
	if(kind==Parent){
		return 0;
	}
	else if(kind==WATCardOffice){
		return 1;
	}
	else if(kind==NameServer){
		return 2;
	}
	else if(kind==Truck){
		return 3;
	}
	else if(kind==BottlingPlant){
		return 4;
	}
	else{
		cout<<kind<<endl;
		cout<<"Incorrect use of get Index\n";
		return -1;
	}
}

//get the buffer index of kinds Student, Vending, Courier
unsigned int Printer::getIndex(Kind kind, unsigned int lid){
	if(kind==Student){
		return 5+lid;
	}
	else if(kind==Vending){
		return 5+numStudents+lid;
	}
	else if(kind==Courier){
		return 5+numStudents+numVendingMachines+lid;
	}
	else{
		cout<<"Incorrect use of get Index\n";
		return -1;
	}
}

void Printer::flushLine(){														//flushline
	for(unsigned int i=0;i<size;i++){
		if(stateBuffer[i]!='%'){												//if state is '%' ignore it
			cout<<stateBuffer[i];
			if(value1Buffer[i]!=-1){											//if values are -1 ignore them
				cout<<value1Buffer[i];
				if(value2Buffer[i]!=-1){
					cout<<","<<value2Buffer[i];									//else output current buffer value
				}
			}
		}
		cout<<"\t";																//reset buffers to ignoreable state
		stateBuffer[i]='%';
		value1Buffer[i]=-1;
		value2Buffer[i]=-1;
	}
	cout<<endl;
}

void Printer::updateBuffer(unsigned int index, char state){						//updates buffers with new values
	updateBuffer(index, state, -1, -1);
}

void Printer::updateBuffer(unsigned int index, char state, int value1){			//updates buffers with new values
	updateBuffer(index, state, value1,-1);
}


void Printer::updateBuffer(unsigned int index, char state, int value1, int value2){	
	//checks if buffer needs to be flushed
	if(stateBuffer[index]!='%'){
		flushLine();
	}
	stateBuffer[index]=state;													//updates buffer values
	value1Buffer[index]=value1;
	value2Buffer[index]=value2;
}

void Printer::finish(unsigned int index){										//flushes all buffers then prints finish message for given index
	flushLine();
	for(unsigned int i=0; i<size;i++){
		if(i==index){
			cout<<"F\t";
		}
		else{
			cout<<"...\t";
		}
	}
	cout<<endl;
}

void Printer::print( Kind kind, char state ){
	unsigned int curId=getIndex(kind);
	//printDebug(curId);
	if(state=='F'){
		finish(curId);
	}
	else{
		updateBuffer(curId,state);
	}
}

void Printer::print( Kind kind, char state, int value1 ){
	unsigned int curId=getIndex(kind);
	//printDebug(curId);
	updateBuffer(curId,state,value1);
}

void Printer::print( Kind kind, char state, int value1, int value2 ){
	unsigned int curId=getIndex(kind);
	//printDebug(curId);
	updateBuffer(curId,state,value1,value2);
}

void Printer::print( Kind kind, unsigned int lid, char state ){
	unsigned int curId=getIndex(kind,lid);
	//printDebug(curId);
	if(state=='F'){
		finish(curId);
	}
	else{
		updateBuffer(curId,state);
	}
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ){
	unsigned int curId=getIndex(kind,lid);
	//printDebug(curId);
	updateBuffer(curId,state,value1);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ){
	unsigned int curId=getIndex(kind,lid);
	//printDebug(curId);
	updateBuffer(curId,state,value1,value2);
}
