#include "synch.h"
#include "ptable.h"

PTable::PTable(int size) {
    int i;
    psize = size;
    for (i = 0; i < size; i++) {
        pcb[i] = NULL;
    }
    bmsem = new Semaphore("bmsem", 1);
}

PTable::~PTable() {
    int i;
    for (i = 0; i < MAX_PROCESS; i++) {
        if (!pcb[i]) delete pcb[i];
    }
    delete bmsem;
}

int PTable::ExecUpdate(char* name) {
    // Gọi mutex->P(); để giúp tránh tình trạng nạp 2 tiến trình cùng 1 lúc.
    bmsem->P();

    // Kiểm tra tính hợp lệ của chương trình “name”.
    // Kiểm tra sự tồn tại của chương trình “name” bằng cách gọi phương thức
    // Open của lớp fileSystem.
    if (name == NULL) {
        DEBUG(dbgSys, "\nPTable::Exec : Can't not execute name is NULL.\n");
        bmsem->V();
        return -1;
    }
    // So sánh tên chương trình và tên của currentThread để chắc chắn rằng
    // chương trình này không gọi thực thi chính nó.
    if (strcmp(name, "./test/scheduler") == 0 ||
        strcmp(name, kernel->currentThread->getName()) == 0) {
        DEBUG(dbgSys, "\nPTable::Exec : Can't not execute itself.\n");
        bmsem->V();
        return -1;
    }

    // Tìm slot trống trong bảng Ptable.
    int index = this->GetFreeSlot();

    // Check if have free slot
    if (index < 0) {
        DEBUG(dbgSys, "\nPTable::Exec :There is no free slot.\n");
        bmsem->V();
        return -1;
    }

    // Nếu có slot trống thì khởi tạo một PCB mới với processID chính là index
    // của slot này
    pcb[index] = new PCB(index);
    pcb[index]->SetFileName(name);

    // parrentID là processID của currentThread
    pcb[index]->parentID = kernel->currentThread->processID;

    // Gọi thực thi phương thức Exec của lớp PCB.
    int pid = pcb[index]->Exec(name, index);

    // Gọi bmsem->V()
    bmsem->V();
    // Trả về kết quả thực thi của PCB->Exec.
    return pid;
}

int PTable::ExitUpdate(int ec) { return 0; }

int PTable::JoinUpdate(int id) {
    // Ta kiểm tra tính hợp lệ của processID id và kiểm tra tiến trình gọi Join có phải là cha của tiến trình có processID là id hay không. Nếu không thỏa, ta báo lỗi hợp lý và trả về -1.
    if (id < 0 || id >= psize || pcb[id] == NULL || pcb[id]->parentID != kernel->currentThread->processID) {
        DEBUG(dbgSys, "\nPTable::Join : Can't not join.\n");
        return -1;
    }
    // Tăng numwait và gọi JoinWait() để chờ tiến trình con thực hiện.
    pcb[pcb[id]->parentID]->IncNumWait();
    pcb[id]->JoinWait();

    // Sau khi tiến trình con thực hiện xong, tiến trình đã được giải phóng

    // Xử lý exitcode.
	int exit_code = pcb[id]->GetExitCode();
    // ExitRelease() để cho phép tiến trình con thoát.
	pcb[id]->ExitRelease();
    return exit_code;
}

int PTable::GetFreeSlot() {
    int i;
    for (i = 0; i < psize; i++) {
        if (!pcb[i]) return i;
    }
    return -1;
}

bool PTable::IsExist(int pid) { return false; }

void PTable::Remove(int pid) {}

char* PTable::GetFileName(int id) { return pcb[id]->GetFileName(); }
