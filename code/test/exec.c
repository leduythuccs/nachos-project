/* exec.c
 *	Simple program to test the exec system call.
 */

// #include "syscall.h"
// #define stdin 0
// #define stdout 1

// int main() {
//     int pid;
//     pid = Exec("num_io");
//     if (pid < 0) {
//         Write("Exec failed: ", 14, stdout);
//         PrintNum(pid);
//     } else
//         Join(pid);
// }


#include "syscall.h"
    #define stdin 0
    #define stdout 1

    int main() {
        int pid, pid1;
        pid = Exec("str_io");
        if (pid < 0) {
            Write("Fork failed: ", 14, stdout);
            PrintNum(pid);
        } else {
            // Child process
            pid1 = Exec("add");
            if (pid1 < 0) {
                Write("Exec failed: ", 14, stdout);
                PrintNum(pid1);
            }
            else {
                // Parent process
                Join(pid);
                Join(pid1);
            }
        }
    }