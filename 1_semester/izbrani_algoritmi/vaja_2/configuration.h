#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>

class Configuration
{
public:
    Configuration();

    static inline const std::string privateKeyFileName = "privateKey.key";
    static inline const std::string publicKeyFileName = "publicKey.key";
};

#endif // CONFIGURATION_H
