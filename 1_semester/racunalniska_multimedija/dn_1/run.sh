FILENAME=test.bmp
OPT=fr
PARAM1=000000000000000011111111
PARAM2=111111110000000000000000

#PARAM1=111
#PARAM2=101

g++ -std=c++17 BinReader.cpp BinWriter.cpp vaja.cpp && ./a.out $FILENAME $OPT $PARAM1 $PARAM2
