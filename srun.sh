#!/bin/bash
gcc -static -g -o tmp tmp.s helper.o
./tmp
echo $?