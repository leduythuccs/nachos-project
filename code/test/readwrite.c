#include "syscall.h"

#define MODE_READWRITE 0
#define MODE_READ 1

int main() {
    char buffer[100];
    int i;
    int write;

    int fileid = Open("abc.txt", MODE_READ);
    int read = Read(buffer, 50, fileid);
    PrintString("Read ");
    PrintNum(read);
    PrintString(" characters: ");
    PrintString(buffer);
    Close(fileid);

    fileid = Open("abc1.txt", MODE_READWRITE);
    write = Write(buffer, read, fileid);

    PrintString("Write ");
    PrintNum(write);
    PrintString(" characters: ");
    PrintString(buffer);
    Close(fileid);

    fileid = Open("abc2.txt", MODE_READWRITE);
    read = Read(buffer, 50, fileid);
    PrintString("Read ");
    PrintNum(read);
    PrintString(" characters: ");
    PrintString(buffer);
    // Write to the same file
    write = Write(buffer, read, fileid);
    PrintString("Write ");
    PrintNum(write);
    PrintString(" characters: ");
    PrintString(buffer);
    Close(fileid);
}
