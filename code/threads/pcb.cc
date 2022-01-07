#include "synch.h"
#include "pcb.h"

PCB::PCB(int id) {
    this->parentID = kernel->currentThread->processID;
    joinsem = new Semaphore("joinsem", 1);
    exitsem = new Semaphore("exitsem", 1);
    multex = new Semaphore("multex", 1);
}

PCB::~PCB() {
    delete joinsem;
    delete exitsem;
    delete multex;

    if (thread) {
        thread->FreeSpace();
        thread->Finish();
        // delete thread;
    }

    delete[] filename;
}

void StartProcess_2(void* pid) {
    int id;
    id = *((int*)pid);
    // Lay fileName cua process id nay
    char* fileName = kernel->pTab->GetFileName(id);

    AddrSpace* space;
    space = new AddrSpace(fileName);

    if (space == NULL) {
        printf("\nPCB::Exec: Can't create AddSpace.");
        return;
    }

    space->Execute();
    // kernel->currentThread->space = space;

    // space->InitRegisters();	// set the initial register values
    // space->RestoreState();	// load page table register

    // kernel->machine->Run();	// jump to the user progam
    ASSERT(FALSE);  // machine->Run never returns;
                    // the address space exits
                    // by doing the syscall "exit"
}

int PCB::Exec(char* filename, int id) {
    // cerr << filename << ' ' << pid << endl;
    multex->P();

    this->thread = new Thread(filename, true);
    if (this->thread == NULL) {
        printf("\nPCB::Exec: Not enough memory!\n");
        multex->V();  // Nha CPU de nhuong CPU cho tien trinh khac
        return -1;    // Tra ve -1 neu that bai
    }

    //  Đặt processID của thread này là id.
    this->thread->processID = id;
    // Đặt parrentID của thread này là processID của thread gọi thực thi Exec
    this->parentID = kernel->currentThread->processID;
    // Gọi thực thi Fork(StartProcess_2,id) => Ta cast thread thành kiểu int,
    // sau đó khi xử ký hàm StartProcess ta cast Thread về đúng kiểu của nó.
    this->thread->Fork(StartProcess_2, &id);

    multex->V();
    // Trả về id.
    return id;
}

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

void PCB::SetFileName(char* fn) { strcpy(filename, fn); }

char* PCB::GetFileName() {
    // cerr << "get file name" << ' ' << filename << endl;
    return filename;
}
