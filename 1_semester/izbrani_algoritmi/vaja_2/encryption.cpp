#include "encryption.h"

Encryption::Encryption(long keyParam1, long keyParamN, std::string fileName) : keyParam1(keyParam1), keyParamN(keyParamN), fileName(fileName)
{

}


void Encryption::Encrypt() {
    unsigned int bitsToRead = (unsigned int)std::floor(std::log2(keyParamN));


}
