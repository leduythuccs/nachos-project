#include "syscall.h"

#define CUP_SIZE 10

void main() {
    int studentId;  // student id
    int fillTime;   // number of time that the machine need to fill the cup
    int file_descriptor, file_input;  // file descriptor for shared file, file
                                      // descriptor for input file
    char buffer[4] = " , ";           // for write and reading stuff
    int j = 0;
    int tmp;

    /***********Read the number of students***********/
    file_input = Open("input.txt", 0);
    if (file_input == -1) {
        PrintString("Cannot open file input.txt\n");
        return 1;
    }
    Read(buffer, 1, file_input);
    fillTime = (buffer[0] - '0') * CUP_SIZE;
    Close(file_input);
    /***********END OF Read the number of students***********/

    while (fillTime > 0) {
        --fillTime;
        // wait until there is a student want to drink
        Wait("cup");

        // Read the student number from shared file
        file_descriptor = Open("shared.txt", 1);
        if (file_descriptor == -1) {
            PrintString("Cannot open file shared.txt\n");
            return;
        } else {
            Read(buffer, 1, file_descriptor);
            Close(file_descriptor);
            studentId = buffer[0] - '0';
        }

        // Loop to simulate the filling warter process
        PrintString("Filling water for student ");
        PrintNum(studentId);
        PrintString("\n");

        for (j = RandomNum() % 10000; j >= 0; --j) {
            ;
        }

        file_descriptor = Open("output.txt", 0);
        if (file_descriptor == -1) {
            PrintString("Cannot open file output.txt\n");
        } else {
            tmp = Seek(-1, file_descriptor);
            buffer[0] = studentId + '0';
            buffer[1] = ',';
            Write(buffer, 3, file_descriptor);
            Close(file_descriptor);
        }

        Signal("fill");
    }
}
