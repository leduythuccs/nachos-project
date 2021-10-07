#!/bin/bash
set -e

cd code/test
make

../build.linux/nachos -x halt
../build.linux/nachos -x test_syscall

echo "123" | ../build.linux/nachos -x num_io | grep -q "123Machine halting!"
echo "0" | ../build.linux/nachos -x num_io | grep -q "0Machine halting!"
echo "-0" | ../build.linux/nachos -x num_io | grep -q "0Machine halting!"
echo "-01" | ../build.linux/nachos -x num_io | grep -q "0Machine halting!"
echo "000001" | ../build.linux/nachos -x num_io | grep -q "0Machine halting!"
echo "-1" | ../build.linux/nachos -x num_io | grep -q "\-1Machine halting!"
echo "-2147483648" | ../build.linux/nachos -x num_io | grep -q "\-2147483648Machine halting!"
echo "-2147483649" | ../build.linux/nachos -x num_io | grep -q "0Machine halting!"
echo "2147483647" | ../build.linux/nachos -x num_io | grep -q "2147483647Machine halting!"
echo "2147483648" | ../build.linux/nachos -x num_io | grep -q "0Machine halting!"
echo "3000000000" | ../build.linux/nachos -x num_io | grep -q "0Machine halting!"
echo "-3000000000" | ../build.linux/nachos -x num_io | grep -q "0Machine halting!"


# # Read @ and make sure the output has @
echo "@" | ../build.linux/nachos -x char_io | grep -q "@Machine halting!"
../build.linux/nachos -x random

echo "3 123" | ../build.linux/nachos -x str_io | grep -q "123Machine halting!"
echo "1 123" | ../build.linux/nachos -x str_io | grep -q "1Machine halting!"
echo "256" | ../build.linux/nachos -x str_io -d u 2>&1 >/dev/null | grep -q "String length exceeds 255"
# Print 255 'a's to stdout
echo "255 "$(head -c 255 < /dev/zero | tr '\0' 'a') | \
    ../build.linux/nachos -x str_io | \
    grep -q $(head -c 255 < /dev/zero | tr '\0' 'a')"Machine halting!"

echo "Success!"
