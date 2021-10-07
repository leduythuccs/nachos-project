/* str_io.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do a syscall that read a string and print it
 *
 */

#include "syscall.h"
char a[256];
int main() {
    PrintString("String length: (<= 255):\n");
    ReadString(a, ReadNum());
    PrintString(a);
}
