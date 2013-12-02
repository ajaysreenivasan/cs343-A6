#include "printer.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ){
	this->numStudents = numStudents;
	this->numVendingMachines = numVendingMachines;
	this->numCouriers = numCouriers;
	int idCounter =0;
	for(unsigned int i =0;i<numStudents+numVendingMachines+numCouriers+5;i++){
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
			cout<<"Mach"<<(idCounter++)-numStudents-numVendingMachines;
		}
		buffer.push_back("");
		cout<<"\t";
	}
	cout<<endl;
	for(unsigned int i =0;i<buffer.size();i++){
		cout<<"*******\t";
	}
	cout<<endl;
}

void Printer::printDebug(unsigned int i){
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
	else if(i<5+numStudents){
		cout<<"Stud"<<i-numStudents;
	}
	else if(i<5+numVendingMachines+numStudents){
		cout<<"Mach"<<i-numStudents-numVendingMachines;
	}
	else if(i<5+numVendingMachines+numStudents+numCouriers){
		cout<<"Mach"<<i-numStudents-numVendingMachines-numCouriers;
	}
	cout<<endl;
}

//Parent, WATCardOffice, NameServer, Truck, BottlingPlant
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

//Student, Vending, Courier
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

void Printer::flushLine(){
	for(unsigned int i=0;i<buffer.size();i++){
		cout<<buffer[i]<<"\t";
		buffer[i]="";
	}
	cout<<endl;
}

void Printer::updateBuffer(unsigned int index, string newValue){	//checks if buffer needs to be flushed
	if(buffer[index]!=""){
		flushLine();
	}
	buffer[index]=newValue;											//updates buffer value
}

void Printer::finish(unsigned int index){				//flushes all buffers then prints finish message
	flushLine();										//for given index
	for(unsigned int i=0; i<buffer.size();i++){
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
	printDebug(curId);
	if(state=='F'){
		finish(curId);
	}
	else{
		stringstream ss;
		string bufferValue="";
		ss<<state;
		ss>>bufferValue;
		updateBuffer(curId,bufferValue);
	}
}

void Printer::print( Kind kind, char state, int value1 ){
	unsigned int curId=getIndex(kind);
	printDebug(curId);
	stringstream ss;
	string bufferValue="";
	string stateString="";
	string value1String="";
	ss<<state<<" "<<value1;
	ss>>stateString;
	ss>>value1String;
	bufferValue=stateString+value1String;
	updateBuffer(curId,bufferValue);
}

void Printer::print( Kind kind, char state, int value1, int value2 ){
	unsigned int curId=getIndex(kind);
	printDebug(curId);
	stringstream ss;
	string bufferValue="";
	string stateString="";
	string value1String="";
	string value2String="";
	ss<<state<<" "<<value1<<" "<<value2;
	ss>>stateString;
	ss>>value1String;
	ss>>value2String;
	bufferValue=stateString+value1String+","+value2String;
	updateBuffer(curId,bufferValue);
}

void Printer::print( Kind kind, unsigned int lid, char state ){
	unsigned int curId=getIndex(kind,lid);
	printDebug(curId);
	if(state=='F'){
		finish(curId);
	}
	else{
		stringstream ss;
		string bufferValue="";
		ss<<state;
		ss>>bufferValue;
		updateBuffer(curId,bufferValue);
	}
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ){
	unsigned int curId=getIndex(kind);
	printDebug(curId);
	stringstream ss;
	string bufferValue="";
	string stateString="";
	string value1String="";
	string value2String="";
	ss<<state<<" "<<value1;
	ss>>stateString;
	ss>>value1String;
	ss>>value2String;
	bufferValue=stateString+value1String;
	updateBuffer(curId,bufferValue);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ){
	unsigned int curId=getIndex(kind);
	printDebug(curId);
	stringstream ss;
	string bufferValue="";
	string stateString="";
	string value1String="";
	string value2String="";
	ss<<state<<" "<<value1<<" "<<value2;
	ss>>stateString;
	ss>>value1String;
	ss>>value2String;
	bufferValue=stateString+value1String+","+value2String;
	updateBuffer(curId,bufferValue);
}

// comment