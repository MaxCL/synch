#!/bin/bash
gcc -Wall -W LatticeFunctions.c randomlib.c Operators.c UnimodalFunctions.c VectorOperators.c synch.c -o synch -lm


