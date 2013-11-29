#include <uC++.h>
#include <iostream>
#include <vector>
#include "MPRNG.h"
//#include "printer.h"
#include <cstdlib>

using namespace std;

MPRNG m;

void uMain::main(){
	char * configFile;
    unsigned int S=getpid();
    
    if(argc>=2)
		configFile=argv[1];
    if(argc>=3)
		S=atoi(argv[2]);

    if(S<1){	
	cerr<<"Incorrect parameter usage.\nExpected usage:\nphil [ P>1 [ N>0 [ S>0 ] ] ]\n";
        return;
    }

 	m.seed(S);

    for(unsigned int i =0; i< S; i++){
    	//Philosopher * tempP = new Philosopher(i,N,*t,*p);
        //phils.push_back(tempP);
    }

    //while(!phils.empty()){
    	//delete phils.back();
    	//phils.pop_back();
    //}

    return;
}