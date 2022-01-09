#include "syscall.h"

#define MAX_LENGTH 20
#define MAX_STUDENT 5

int main() {
    int file_input, file_output;  // file descriptor for input, output
    int f_shared;                 // file descriptor for shared variable
    int n;                        // n students
    char buffer[MAX_LENGTH];      // For reading stuff
    int students[MAX_STUDENT];    // Array of students
    int water_machine;            // Water machine
    int tmp, i;                   // tempurary variable, index variable

    /***********Read the number of students***********/
    file_input = Open("input.txt", 0);
    if (file_input == -1) {
        PrintString("Cannot open file input.txt\n");
        return 1;
    }
    Read(buffer, 1, file_input);
    n = buffer[0] - '0';
    Close(file_input);

    if (n > 5) {
        PrintString("Too many students\n");
        return 1;
    }

    PrintString("Number of students: ");
    PrintNum(n);
    PrintString("\n");
    /***********END OF Read the number of students***********/

    /***********Create output file***********/
    if (CreateFile("output.txt")) {
        PrintString("Cannot create file output.txt\n");
        return 1;
    }
    /***********END OF Create output file***********/

    /***********Create shared file***********/
    if (CreateFile("shared.txt")) {
        PrintString("Cannot create file shared.txt\n");
        return 1;
    }
    /***********END OF shared output file***********/

    /***********Create Semaphore***********/
    // only 1 student can put his/her cup in the machine at a time
    tmp = CreateSemaphore("putcup", 1);
    if (tmp == -1) {
        PrintString("Create Semaphore for putcup failed\n");
        return 1;
    }
    // for waiting for the water machine to fill the cup
    tmp = CreateSemaphore("fill", 0);
    if (tmp == -1) {
        PrintString("Create Semaphore for fill failed\n");
        return 1;
    }
    // this is for the water machine to wait for the cup
    tmp = CreateSemaphore("cup", 0);
    if (tmp == -1) {
        PrintString("Create Semaphore for cup failed\n");
        return 1;
    }
    /***********END OF Create Semaphore***********/

    /***********Spawn child process**********/
    for (i = 0; i < n; i++) {
        students[i] = Exec("sinhvien");
        if (students[i] == -1) {
            PrintString("Create student failed\n");
            return 1;
        }
    }
    water_machine = Exec("voinuoc");
    if (water_machine == 1) {
        PrintString("Create water machine failed\n");
        return 1;
    }
    for (i = 0; i < n; i++) {
        Join(students[i]);
    }
    Join(water_machine);
    /***********END OF Spawn child process**********/

    /***********Remove the last `,` in output file**********/
    file_output = Open("output.txt", 0);
    if (file_output == -1) {
        PrintString("Cannot open file output.txt\n");
    } else {
        int tmp = Seek(-1, file_output);
        Seek(tmp - 2, file_output);
        Write("  ", 2, file_output);
        Close(file_output);
    }
    /***********End of Remove the last `,` in output file**********/
    PrintString("\nDone\n");
    return 0;
}
