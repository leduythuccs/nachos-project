#ifndef STABLE_H
#define STABLE_H

#include "bitmap.h"
#include "sem.h"
#define MAX_SEMAPHORE 10

class STable {
   private:
    Bitmap* bm;
    Sem* semTab[MAX_SEMAPHORE];

   public:
    STable();
    ~STable();
    int Create(char* name, int init);
    int Wait(char* name);
    int Signal(char* name);
    int FindFreeSlot();
};

#endif