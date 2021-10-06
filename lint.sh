#!/bin/bash
set -e

find code/ -iname *.h -o -iname *.cc -o -iname *.c | xargs clang-format -i
