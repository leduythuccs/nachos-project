// synchconsole.cc
//	Routines providing synchronized access to the keyboard
//	and console display hardware devices.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "synchconsole.h"

//----------------------------------------------------------------------
// SynchConsoleInput::SynchConsoleInput
//      Initialize synchronized access to the keyboard
//
//      "inputFile" -- if NULL, use stdin as console device
//              otherwise, read from this file
//----------------------------------------------------------------------

SynchConsoleInput::SynchConsoleInput(char *inputFile) {
    consoleInput = new ConsoleInput(inputFile, this);
    lock = new Lock("console in");
    waitFor = new Semaphore("console in", 0);
}

//----------------------------------------------------------------------
// SynchConsoleInput::~SynchConsoleInput
//      Deallocate data structures for synchronized access to the keyboard
//----------------------------------------------------------------------

SynchConsoleInput::~SynchConsoleInput() {
    delete consoleInput;
    delete lock;
    delete waitFor;
}

//----------------------------------------------------------------------
// SynchConsoleInput::GetChar
//      Read a character typed at the keyboard, waiting if necessary.
//----------------------------------------------------------------------

char SynchConsoleInput::GetChar() {
    char ch;

    lock->Acquire();
    waitFor->P();  // wait for EOF or a char to be available.
    ch = consoleInput->GetChar();
    lock->Release();
    return ch;
}

//----------------------------------------------------------------------
// SynchConsoleInput::GetString
//      Read a string from keyboard to buffer, return number of read characters.
//----------------------------------------------------------------------

int SynchConsoleInput::GetString(char *buffer, int size) {
    for (int i = 0; i < size; ++i) {
        buffer[i] = GetChar();
        if (buffer[i] == EOF) {
            buffer[i] = 0;
            return -2;
        }
    }
    return size;
}

//----------------------------------------------------------------------
// SynchConsoleInput::CallBack
//      Interrupt handler called when keystroke is hit; wake up
//	anyone waiting.
//----------------------------------------------------------------------

void SynchConsoleInput::CallBack() { waitFor->V(); }

//----------------------------------------------------------------------
// SynchConsoleOutput::SynchConsoleOutput
//      Initialize synchronized access to the console display
//
//      "outputFile" -- if NULL, use stdout as console device
//              otherwise, read from this file
//----------------------------------------------------------------------

SynchConsoleOutput::SynchConsoleOutput(char *outputFile) {
    consoleOutput = new ConsoleOutput(outputFile, this);
    lock = new Lock("console out");
    waitFor = new Semaphore("console out", 0);
}

//----------------------------------------------------------------------
// SynchConsoleOutput::~SynchConsoleOutput
//      Deallocate data structures for synchronized access to the keyboard
//----------------------------------------------------------------------

SynchConsoleOutput::~SynchConsoleOutput() {
    delete consoleOutput;
    delete lock;
    delete waitFor;
}

//----------------------------------------------------------------------
// SynchConsoleOutput::PutChar
//      Write a character to the console display, waiting if necessary.
//----------------------------------------------------------------------

void SynchConsoleOutput::PutChar(char ch) {
    lock->Acquire();
    consoleOutput->PutChar(ch);
    waitFor->P();
    lock->Release();
}

//----------------------------------------------------------------------
// SynchConsoleOutput::PutString
//      Write a string to the console display, return number of written
//      charaters.
//----------------------------------------------------------------------

int SynchConsoleOutput::PutString(char *buffer, int size) {
    for (int i = 0; i < size; ++i) PutChar(buffer[i]);
    return size;
}

//----------------------------------------------------------------------
// SynchConsoleOutput::CallBack
//      Interrupt handler called when it's safe to send the next
//	character can be sent to the display.
//----------------------------------------------------------------------

void SynchConsoleOutput::CallBack() { waitFor->V(); }
