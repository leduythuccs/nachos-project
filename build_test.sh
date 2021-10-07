#!/bin/bash
set -e

cd code/test
make

../build.linux/nachos -x halt
../build.linux/nachos -x test_syscall

# Read @ and make sure the output has @
echo "@" | ../build.linux/nachos -x char_io | grep -q '@'
../build.linux/nachos -x random
