#include "syscall.h"

int main() {
    int i;
    for (i = 32; i <= 126; i++) {
        PrintNum(i);
        PrintChar(' ');
        PrintChar((char)i);
        PrintChar('\n');
    }
}
