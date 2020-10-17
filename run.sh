#!/bin/bash -x
./9cc $1 > tmp.s
gcc -static -O3 -o  tmp tmp.s helper.o
./tmp
echo ret: $?