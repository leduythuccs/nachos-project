#!/bin/bash
set -e

cd code/test
make

../build.linux/nachos -x halt
../build.linux/nachos -x test_syscall
