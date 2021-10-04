#!/bin/bash
set -e

sudo apt-get install gcc g++ gcc-multilib g++-multilib make

cd ..
wget https://www.fit.hcmus.edu.vn/~ntquan/os/assignment/mips-decstation.linux-xgcc.gz
tar zxvf mips-decstation.linux-xgcc.gz
