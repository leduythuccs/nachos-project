/* exec.c
 *	Simple program to test the exec system call.
 */

#include "syscall.h"

int main() {
    // Exec("test/help");
    Exec("help");
    // Exec("num_io");
    Exec("random");
    // Exec("halt");
}
