#!/bin/bash
gcc -static -o tmp tmp.s helper.o
./tmp
echo $?