/* char_io.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do a add syscall that read a character and print it
 *
 */

#include "syscall.h"

int main() { PrintChar(ReadChar()); }
