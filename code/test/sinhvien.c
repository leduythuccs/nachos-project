#include "syscall.h"

#define CUP_SIZE 10

void main() {
    int i = 0;
    int pid = GetPid();
    int j = 0;
    int run_time = 0;
    int file_descriptor;
    char buffer[4] = " , ";
    int tmp;

    for (i = 0; i < CUP_SIZE; ++i) {
        Wait("voinuoc");
        // Loop to simulate the filling warter process
        for (j = RandomNum() % 10000; j >= 0; --j) {
            ;
        }
        file_descriptor = Open("output.txt", 0);
        if (file_descriptor == -1) {
            PrintString("Cannot open file output.txt\n");
        } else {
            int tmp = Seek(-1, file_descriptor);
            buffer[0] = pid + '0';
            Write(buffer, 3, file_descriptor);
            Close(file_descriptor);
        }
        Signal("voinuoc");
    }
}
