#!/bin/bash

set + x

FLAGS="$(pkg-config --cflags --libs opencv4)"

INFILE=lena_color.bmp
OPTION=c
OUTFILE=out.bin
THR=10

g++ -w -O3 -std=c++17 main.cpp $FLAGS && ./a.out $INFILE $OPTION $OUTFILE $THR
