#include "syscall.h"

#define MODE_READWRITE 0
#define MODE_READ 1

#define stdin 0
#define stdout 1

int main() {
    char buffer[100];
    int i;
    int write;

    int fileid = Open("abc.txt", MODE_READ);
    int read = Read(buffer, 50, fileid);
    int len = 0;
    while (buffer[len] != '\0') ++len;
    PrintString("Read ");
    PrintNum(len);
    PrintString(" characters: ");
    PrintString(buffer);
    PrintString("\n");
    Close(fileid);

    fileid = Open("abc1.txt", MODE_READWRITE);
    write = Write(buffer, len, fileid);

    PrintString("Write ");
    PrintNum(write);
    PrintString(" characters: ");
    PrintString(buffer);
    PrintString("\n");
    Close(fileid);

    fileid = Open("abc2.txt", MODE_READWRITE);
    read = Read(buffer, 50, fileid);
    len = 0;
    while (buffer[len] != '\0') ++len;

    PrintString("Read ");
    PrintNum(len);
    PrintString(" characters: ");
    PrintString(buffer);
    PrintString("\n");
    // Write to the same file
    write = Write(buffer, len, fileid);
    PrintString("Write ");
    PrintNum(write);
    PrintString(" characters: ");
    PrintString(buffer);
    PrintString("\n");
    Close(fileid);

    PrintString("Type a string (use ctrl+D to end typing):\n");
    for (i = 0; i < len; ++i) {
        buffer[i] = 0;
    }
    Read(buffer, 50, stdin);
    len = 0;
    while (buffer[len] != '\0') ++len;
    PrintNum(Write(buffer, len, stdout));
}
