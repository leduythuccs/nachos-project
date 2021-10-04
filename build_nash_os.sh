#!/bin/bash
set -e

cd code/build.linux
make depend
make

# Test
./nachos
