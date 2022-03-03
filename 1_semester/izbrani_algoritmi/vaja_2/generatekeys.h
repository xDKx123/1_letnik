#ifndef GENERATEKEYS_H
#define GENERATEKEYS_H

#include <tuple>

#include "millerrabin.h"
#include "utils.h"


class GenerateKeys
{
private:
    //Variables
    unsigned int bitSize;
    Utils* utils;
    MillerRabin* mr;

    //Methods
    long modularLinearEquationSolver(unsigned long a, unsigned long b, unsigned long n);
    void extendedEuclid(unsigned long a, unsigned long b, long& d, long& x, long& y);
    std::tuple<long, long, long> extendedEuclidIterative(long a, long b);

    long eNumber(long sigma);


public:
    GenerateKeys(unsigned int bitSize);
    ~GenerateKeys();

    unsigned long modularExponentation(unsigned long a, unsigned long b, unsigned long n);
    std::tuple<long, long, long> generate();


};

#endif // GENERATEKEYS_H
