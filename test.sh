#!/bin/bash
try() {
  expected="$1"
  input="$2"

  ./9cc "$input" > tmp.s
  gcc -o tmp tmp.s
  ./tmp
  actual="$?"

  if [ "$actual" = "$expected" ]; then
    echo "$input => $actual"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}

try 0 0
try 101 101
try 42 42
try 0 "42+42-40-40-1-1-1-1"
try 0 "42 +42 -40  -40-     1 -1-1-1"
try 41 " 12 + 34 - 5 "
try 2 "1+1"
try 47 "5+6*7"
try 15 "5*(9-6)"
try 4 "(3+5)/2"
try 13 "1   * ( 2* ( 2  +1+2*(6-1)       ))/(  6 /( 2 +1))  "
try 4 "-10+14"
try 4 "+14-10"
try 3  "-(-(-(-3)))"
try 1 "1==1"
try 0 "2==1"
try 1 "(1+1-2+1)==1"
try 1 "1==((1==2)+(-1==-1))==1"


echo OK