#include "bruteforce.h"

BruteForce::BruteForce() : randomNumber(0)
{

}

BruteForce::BruteForce(long randomNumber) : randomNumber(randomNumber) {}

unsigned long BruteForce::algorithm(unsigned long randomNumber)
{
    //long randomNumber = Utils::random(100, 1000);

    if (randomNumber % 2 == 0) {
        ++randomNumber;
    }

    while (true) {
        int index = 3;

        while (randomNumber % index != 0 && index <= std::sqrt(randomNumber)) {
            index+=2;
        }

        if (index > std::sqrt(randomNumber)) {
            return randomNumber;
        }

        randomNumber+=2;
    }
}
