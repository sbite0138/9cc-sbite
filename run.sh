#!/bin/bash
./9cc -e "$1" > tmp.s
gcc -static -o tmp tmp.s helper.o
./tmp
echo $?