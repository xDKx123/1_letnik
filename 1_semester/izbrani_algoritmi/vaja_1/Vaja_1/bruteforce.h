#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "utils.h"
#include <iostream>
#include <cmath>

class BruteForce
{
private:
    long randomNumber;
public:
    BruteForce();
    BruteForce(long randomNumber);

    unsigned long algorithm(unsigned long randomNumber);
};

#endif // BRUTEFORCE_H
