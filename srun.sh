#!/bin/bash
gcc -o tmp tmp.s helper.o
./tmp
echo $?