#include "utils.h"

Utils::Utils() : currentStatus(1)
{

}

long Utils::random(long min, long max) {
    //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    //std::minstd_rand0 generator (seed);

    currentStatus = LCG((long)UINT32_MAX +1, 69069, 0, currentStatus);
    return min + currentStatus % (max - min + 1);
    //return min + generator() % (max - min + 1);
}

long Utils::LCG(long m, long a, long b, long r0) {
    return (a*r0 + b ) % m;
}
