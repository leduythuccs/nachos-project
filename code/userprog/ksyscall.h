/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__
#define __USERPROG_KSYSCALL_H__

#include "kernel.h"
#include "synchconsole.h"
#include "ksyscallhelper.h"
#include <stdlib.h>

void SysHalt() { kernel->interrupt->Halt(); }

int SysAdd(int op1, int op2) { return op1 + op2; }

int SysReadNum() {
    readUntilBlank();

    int len = strlen(_numberBuffer);
    // Read nothing -> return 0
    if (len == 0) return 0;

    // Check comment below to understand this line of code
    if (strcmp(_numberBuffer, "-2147483648") == 0) return INT32_MIN;

    bool nega = (_numberBuffer[0] == '-');
    int zeros = 0;
    bool is_leading = true;
    int num = 0;
    for (int i = nega; i < len; ++i) {
        char c = _numberBuffer[i];
        if (c == '0' && is_leading)
            ++zeros;
        else
            is_leading = false;
        if (c < '0' || c > '9') {
            DEBUG(dbgSys, "Expected number but " << _numberBuffer << " found");
            return 0;
        }
        num = num * 10 + (c - '0');
    }

    // 00            01 or -0
    if (zeros > 1 || (zeros && (num || nega))) {
        DEBUG(dbgSys, "Expected number but " << _numberBuffer << " found");
        return 0;
    }

    if (nega)
        /**
         * This is why we need to handle -2147483648 individually:
         * 2147483648 is larger than the range of int32
         */
        num = -num;

    // It's safe to return directly if the number is small
    if (len <= MAX_NUM_LENGTH - 2) return num;

    /**
     * We need to make sure that number is equal to the number in the buffer.
     *
     * Ask: Why do we need that?
     * Answer: Because it's impossible to tell whether the number is bigger
     * than INT32_MAX or smaller than INT32_MIN if it has the same length.
     *
     * For example: 3 000 000 000.
     *
     * In that case, that number will cause an overflow. However, C++
     * doens't raise interger overflow, so we need to make sure that the input
     * string and the output number is equal.
     *
     */
    if (compareNumAndString(num, _numberBuffer))
        return num;
    else
        DEBUG(dbgSys,
              "Expected int32 number but " << _numberBuffer << " found");

    return 0;
}

void SysPrintNum(int num) {
    if (num == 0) return kernel->synchConsoleOut->PutChar('0');

    if (num == INT32_MIN) {
        kernel->synchConsoleOut->PutChar('-');
        for (int i = 0; i < 10; ++i)
            kernel->synchConsoleOut->PutChar("2147483648"[i]);
        return;
    }

    if (num < 0) {
        kernel->synchConsoleOut->PutChar('-');
        num = -num;
    }
    int n = 0;
    while (num) {
        _numberBuffer[n++] = num % 10;
        num /= 10;
    }
    for (int i = n - 1; i >= 0; --i)
        kernel->synchConsoleOut->PutChar(_numberBuffer[i] + '0');
}

char SysReadChar() { return kernel->synchConsoleIn->GetChar(); }

void SysPrintChar(char character) {
    kernel->synchConsoleOut->PutChar(character);
}

int SysRandomNum() { return random(); }

char* SysReadString(int length) {
    char* buffer = new char[length + 1];
    for (int i = 0; i < length; i++) {
        buffer[i] = SysReadChar();
    }
    buffer[length] = '\0';
    return buffer;
}

void SysPrintString(char* buffer, int length) {
    for (int i = 0; i < length; i++) {
        kernel->synchConsoleOut->PutChar(buffer[i]);
    }
}

bool SysCreateFile(char* fileName) {
    bool success;
    int fileNameLength = strlen(fileName);

    if (fileNameLength == 0) {
        DEBUG(dbgSys, "\nFile name can't be empty");
        success = false;

    } else if (fileName == NULL) {
        DEBUG(dbgSys, "\nNot enough memory in system");
        success = false;

    } else {
        DEBUG(dbgSys, "\nFile's name read successfully");
        if (!kernel->fileSystem->Create(fileName)) {
            DEBUG(dbgSys, "\nError creating file");
            success = false;
        } else {
            success = true;
        }
    }

    return success;
}

int SysOpen(char* fileName, int type){
    if (type != 0 && type != 1) return -1;

    int id = kernel->fileSystem->fileTable->Insert(fileName, type);
    if (id == -1) return -1;
    DEBUG(dbgSys, "\nOpened file");
    return id;
    
}

int SysClose(int id){
    int res = kernel->fileSystem->fileTable->Remove(id);
    return res;
}
#endif /* ! __USERPROG_KSYSCALL_H__ */
