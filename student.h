#ifndef __STUDENT__
#define __STUDENT__

#include "printer.h"
#include "nameServer.h"
#include "watCardOffice.h"
#include "watcard.h"

_Task Student {
    void main();
    Printer * p;
    NameServer * ns;
    WATCardOffice * wco;
    WATCard::FWATCard fw;
    unsigned int id, numToPurchase;
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif