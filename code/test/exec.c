/* exec.c
 *	Simple program to test the exec system call.
 */

#include "syscall.h"

int main() {
    int x = Exec("help");
    Join(x);
}
