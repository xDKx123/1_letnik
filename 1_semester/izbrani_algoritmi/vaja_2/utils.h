#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <vector>
#include <bitset>

#include "configuration.h"

#include <QListWidget>
//#include "millerrabin.h"
//#include "bruteforce.h"

class Utils
{
private:
    long currentStatus;
public:
    Utils();

    long random(long min, long max);
    long LCG(long m, long a, long b, long r0);
    static void addText(QListWidget *listWidget, std::string text);
    static void writeKeys(long e, long s, long n);
    static std::tuple<long, long> readKey(std::string fileName);

    static std::vector<long> fileContent(std::string fileName, unsigned long readBits);

};

#endif // UTILS_H
