#include "syscall.h"

#define MAX_LENGTH 20
#define MAX_STUDENT 5

int main() {
    int f_input; // file descriptor for input
    int n; //n students
    char buffer[MAX_LENGTH]; // For reading stuff
    int students[MAX_STUDENT]; // Array of students
    int tmp, i; // tempurary variable, index variable

    /***********Read the number of students***********/
    f_input = Open("input.txt", 0);
    if (f_input == -1) {
        PrintString("Cannot open file input.txt\n");
        return 1;
    }
    Read(buffer, 1, f_input);
    n = buffer[0] - '0';
    Close(f_input);

    if (n > 5) {
        PrintString("Too many students\n");
        return 1;
    }

    PrintString("Number of students: ");
    PrintNum(n);
    PrintString("\n");
    /***********END OF Read the number of students***********/

    /***********Create voinuoc Semaphore***********/
    tmp = CreateSemaphore("voinuoc", 1);
    if (tmp == -1) {
        PrintString("Create Semaphore for voinuoc failed\n");
        return 1;
    }
    /***********END OF Create voinuoc Semaphore***********/


    /***********Spawn child process**********/
    for (i = 0; i < n; i++) {
        students[i] = Exec("sinhvien");
        if (students[i] == -1) {
            PrintString("Create student failed\n");
            return 1;
        }
    }
    for (i = 0; i < n; i++) {
        Join(students[i]);
    }
    /***********END OF Spawn child process**********/
    PrintString("\nDone\n");
    return 0;
}
