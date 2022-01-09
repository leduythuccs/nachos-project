#include "syscall.h"

#define CUP_SIZE 10

void main() {
    int pid = GetPid();
    int file_descriptor;
    char buffer;
    int i = 0;

    for (i = 0; i < CUP_SIZE; ++i) {
        Wait("putcup");

        // Write to the shared file to notify the water machine
        file_descriptor = Open("shared.txt", 0);
        if (file_descriptor == -1) {
            PrintString("Cannot open file shared.txt\n");
        } else {
            buffer = pid + '0';
            Write(&buffer, 1, file_descriptor);
            Close(file_descriptor);
        }
        // notify the water machine
        Signal("cup");
        // wait for the water machine to filling the cup
        Wait("fill");

        Signal("putcup");
    }
}
