#ifndef MILLERRABIN_H
#define MILLERRABIN_H

#include <bitset>

#include "utils.h"

class MillerRabin
{
private:
    int bitLength;
    unsigned long p,s;
public:
    MillerRabin();
    MillerRabin(int bitLength, unsigned long p, unsigned long s);

    long algorithm(int bitLength, unsigned long p, unsigned long s, Utils* utils);
    long modular_exponentiation(unsigned long a, unsigned long b, unsigned long n);
};

#endif // MILLERRABIN_H
