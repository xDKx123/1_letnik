#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <math.h>

class Encryption
{
    long keyParam1;
    long keyParamN;
    std::string fileName;

public:
    Encryption(long keyParam1, long keyParamN, std::string fileName);

    void Encrypt();
};

#endif // ENCRYPTION_H
