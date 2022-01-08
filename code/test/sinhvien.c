#include "syscall.h"

#define CUP_SIZE 10

void main() {
    int i = 0;
	int x = GetPid();
	int j = 0;
	int run_time = 0;

	for (i = 0; i < CUP_SIZE; ++i) {
		Wait("voinuoc");
		// Loop to simulate the filling warter process
		for (j = RandomNum() % 1000; j >= 0; --j) {
			;
		}
		PrintNum(x);
		Signal("voinuoc");
	}
}
