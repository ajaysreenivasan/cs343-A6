#ifndef __STUDENT__
#define __STUDENT__

#include "printer.h"
#include "nameServer.h"
#include "watCardOffice.h"

_Task Student {
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif