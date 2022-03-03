#include "generatekeys.h"

GenerateKeys::GenerateKeys(unsigned int bitSize) : bitSize(bitSize), utils(new Utils()), mr(new MillerRabin())
{
}

GenerateKeys::~GenerateKeys()
{

}

std::tuple<long, long, long> GenerateKeys::generate(){
    try {

    //Max and min number for bitSize;
    long max = pow(2,bitSize) -1;
    long min = pow(2, bitSize-1);

    long p = 0;
    long q = 0;

    while (p == q) {
        long randomNum = utils->random(min,max);

        p = mr->algorithm(bitSize, randomNum, 10, utils);

        randomNum = utils->random(min,max);
        q = mr->algorithm(bitSize, randomNum, 10, utils);
    }


    long n = p*q;

    long fn = (p-1)*(q-1);

    //auto [d, x, y] = extendedEuclidIterative(p,q);

    long e = eNumber(fn);

    long s = modularLinearEquationSolver(e, 1, fn);

    return {e, s, n};

    }catch (...) {
        throw;
    }

}

long GenerateKeys::modularLinearEquationSolver(unsigned long a, unsigned long b, unsigned long n) {
    //unsigned long a = 98;
    //unsigned long b = 35;
//    long d;
//    long x;
//    long y;

    //extendedEuclid(a,n,d,x,y);

    auto [d,x,y] = extendedEuclidIterative(a,n);


    if (b % d == 0) {
        //call something?
        long x0 = x * (b / d) % n;

        if (d == 1) {
            return x0;
        }
        throw 1;

//        for (unsigned long i = 0; i < d-1; i++) {

//        }
    }
    throw 2;
}

void GenerateKeys::extendedEuclid(unsigned long a, unsigned long b, long& d, long& x, long& y) {
    if (b == 0) {
        d = a;
        x = 1;
        y = 0;
    }
    else {
        long n_x, n_y, n_d;
        extendedEuclid(b, a % b, n_d, n_x, n_y);
        d = n_d;
        x = n_y;
        y = n_x - ((a/b)*n_y);
    }
}

std::tuple<long, long, long> GenerateKeys::extendedEuclidIterative(long a, long b) {
    long x = 0;
    long lastx = 1;
    long y = 1;
    long lasty = 0;

    while (b!=0) {
        long q = a / b;
        long temp = b;
        b = a % b;
        a = temp;
        temp = x;
        x = lastx - q*x;
        lastx = temp;
        temp = y;
        y = lasty - q*y;
        lasty = temp;
    }

    return {a, lastx, lasty};
}

unsigned long GenerateKeys::modularExponentation(unsigned long a, unsigned long b, unsigned long n) {
    unsigned long d = 1;
    std::bitset<64> bits(b);

    int x = 63;

    while (bits[x] == false) {
        x--;
    }

    for (; x >= 0; x--) {
        d = (d*d) % n;
        if (bits[x]) {
            d = (d*a) % n;
        }
    }

    return d;
}

long GenerateKeys::eNumber(long sigma) {
    Utils *s = new Utils();

    while (true) {
        long number = s->random(1, sigma);

        if (number%2 == 0) {
            ++number;
        }

        auto [d,x,y] = extendedEuclidIterative(number, sigma);

        if (d == 1) {
            return number;
        }
    }
}

