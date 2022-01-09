/* test_semaphore.c
 * Simple program to test whether the CreateSemaphore, Wait, Signal system call
 * works.
 */

#include "syscall.h"
int main() {
    int f_success = CreateSemaphore("testSem", 1);
    if (f_success == -1) {
        PrintString("CreateSemaphore failed\n");
        return 1;
    }
    Wait("testSem");
    Signal("testSem");
    PrintString("testSemaphore passed\n");
}
