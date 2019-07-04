#!/bin/bash
gcc -Wall -W VectorOperators.c randomlib.c cic.c -o cic -lm
./cic
