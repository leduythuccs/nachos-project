#include "sem.h"
#include "synch.h"

Sem::Sem(char* na, int i) {
    strcpy(this->name, na);
    sem = new Semaphore(this->name, i);
}

Sem::~Sem() {
    if (sem) delete sem;
}

void Sem::wait() { sem->P(); }  // Down(sem)

void Sem::signal() { sem->V(); }  // Up(sem)

char* Sem::GetName() { return this->name; }
