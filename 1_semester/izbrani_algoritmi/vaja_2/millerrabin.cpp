#include "millerrabin.h"

MillerRabin::MillerRabin() : bitLength(8)
{

}

MillerRabin::MillerRabin(int bitLength, unsigned long p, unsigned long s) : bitLength(bitLength), p(p), s(s)
{

}

long MillerRabin::modular_exponentiation(long a, long b, long n) {
    long d = 1;
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

long MillerRabin::algorithm(int bitLength, long p, long s, Utils* utils) {
    if (p <= 1) {
        p++;
    }
    if (p<=3) {
        return p;
    }
    if (p % 2 == 0) {
        p++;
    }

    this->bitLength = bitLength;

    while (true) {
        long d = p-1;
        long k = 0;

        while (d % 2 == 0) {
            d /=2;
            k++;
        }

        bool returnNum = true;
        for (long j = 1; j <= s; j++) {
            long a = utils->random(2, p - 2);

            //long x = (long)std::pow(a, d) % p;
            long x = modular_exponentiation(a,d,p);

            if (x == 1) {
                continue;
            }

            for (int i = 0; i < k-1; i++) {
                if (x == p-1) {
                    break;
                }
                x = (long)pow(x,2) % p;
            }

            if (x != p-1) {
                p+=2;
                returnNum = false;
                break;
            }
        }

        if (returnNum) {
            return p;
        }
    }

}
