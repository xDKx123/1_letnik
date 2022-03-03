#!/bin/bash

set + x

#FLAGS="$(pkg-config --cflags --libs opencv4)"

INFILE=korpus/kas-4000.text.xml
#OPTION=c
#OUTFILE=out.bin
#THR=10

#g++ -w -O3 -std=c++17 main.cpp $FLAGS && ./a.out $INFILE $OPTION $OUTFILE $THR

#g++ -w -O3 -std=c++17 main.cpp && ./a.out $(cd korpus && realpath $(ls))

g++ -w -O3 -std=c++17 main.cpp && ./a.out $INFILE