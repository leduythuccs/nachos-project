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

../build.linux/nachos -x ascii | grep -q "33 !"
../build.linux/nachos -x ascii | grep -q "126 ~"
echo "5 3 4 1 5 2 1" | ../build.linux/nachos -x bubblesort | grep -q '1 2 3 4 5 Machine halting!'
echo "5 3 4 1 5 2 2" | ../build.linux/nachos -x bubblesort | grep -q '5 4 3 2 1 Machine halting!'
echo "5 -3 4 1 -5 2 1" | ../build.linux/nachos -x bubblesort | grep -q '\-5 \-3 1 2 4 Machine halting!'
echo "a 5 3 4 1 5 2 1" | ../build.linux/nachos -x bubblesort | grep -q 'Sorted array: Machine halting!'
echo "-5 5 3 4 1 5 2 1" | ../build.linux/nachos -x bubblesort | grep -q 'n has to be an integer between 1 and 100 (inclusive), please try again'
echo "101 5 3 4 1 5 2 1" | ../build.linux/nachos -x bubblesort | grep -q 'n has to be an integer between 1 and 100 (inclusive), please try again'
echo "5 3 4 1 5 2 3 1" | ../build.linux/nachos -x bubblesort | grep -q 'Wrong input, please try again'
echo "5 a 4 1 5 2 1" | ../build.linux/nachos -x bubblesort | grep -q '0 1 2 4 5 Machine halting!'

../build.linux/nachos -x help | grep -q "\- The program will print out the sorted array and then exit"

echo "0" | ../build.linux/nachos -x create_file | grep -q 'Create file failed'
echo "a" | ../build.linux/nachos -x create_file | grep -q 'Create file failed'

echo "7 abc.txt" | ../build.linux/nachos -x create_file
test -f "abc.txt"

mkdir -p "xyz"
echo "11 xyz/abc.txt" | ../build.linux/nachos -x create_file
test -f "xyz/abc.txt"

echo "random text to write to file" > "abc.txt"
echo "" > "abc1.txt"
echo "random text to write to file" > "abc2.txt"
printf "random text to write to file\nrandom text to write to file\n" > "abc3.txt"

echo "random text to read from console" | ../build.linux/nachos -x readwrite | grep -q 'random text to read from console'

diff -q abc.txt abc1.txt
diff -q abc2.txt abc3.txt

printf "123" | ../build.linux/nachos -x exec | grep -q '123'

../build.linux/nachos -x test_sem | grep -q 'testSemaphore passed'

echo "5" > "input.txt"
# run in 5 seconds and check if the output is correct
timeout 5 ../build.linux/nachos -x main | grep -q 'Done'

echo "Success!"
