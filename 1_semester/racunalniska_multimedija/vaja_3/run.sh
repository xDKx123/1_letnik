#!/bin/bash

set + x

FLAGS="$(pkg-config --cflags --libs opencv4)"

#FILENAME=lena_color.bmp
#OUTFILE=out.bin
FILENAME=out.bin
OUTFILE=out.bmp
#OPTION=test
#OPTION=h
OPTION=e
MESSAGE=message.txt
N=5
M=5

g++ -std=c++17 main.cpp $FLAGS && ./a.out $FILENAME $OPTION $MESSAGE $N $M $OUTFILE