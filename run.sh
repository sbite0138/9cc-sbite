#!/bin/bash
./9cc $1 > tmp.s
gcc -static -O3 -o  tmp tmp.s helper.o
./tmp
ret=$?
echo ret: $ret
exit $ret
