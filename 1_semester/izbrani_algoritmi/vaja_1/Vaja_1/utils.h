#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <chrono>
#include <random>

//#include "millerrabin.h"
//#include "bruteforce.h"

class Utils
{
private:
    unsigned long currentStatus;
public:
    Utils();

    long random(long min, long max);
    long LCG(long m, long a, long b, long r0);
};

#endif // UTILS_H
