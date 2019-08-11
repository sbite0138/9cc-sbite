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
echo OK