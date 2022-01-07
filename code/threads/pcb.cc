#include "synch.h"
#include "pcb.h"

PCB::PCB(int id) {}

PCB::~PCB() {}

int PCB::Exec(char *filename, int pid) { return 0; }

int PCB::GetID() { return 0; }

int PCB::GetNumWait() { return 0; }

void PCB::JoinWait() {}

void PCB::ExitWait() {}

void PCB::JoinRelease() {}

void PCB::ExitRelease() {}

void PCB::IncNumWait() {}

void PCB::DecNumWait() {}

void PCB::SetExitCode(int ec) {}

int PCB::GetExitCode() { return 0; }

void PCB::SetFileName(char *fn) {}

char PCB::*GetFileName() { return 0; }
