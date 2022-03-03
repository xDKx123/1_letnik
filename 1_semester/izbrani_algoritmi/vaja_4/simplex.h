#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <algorithm>
#include <vector>
#include <limits>

#include "utils.h"

const double infinity = std::numeric_limits<double>::max();

class Simplex
{
private:
    int n,m;
//    std::vector<std::vector<double>> matrix;
//    std::vector<double> bT;
//    std::vector<double> cT;

    std::tuple<std::vector<int>,std::vector<int>, double> initialize(std::vector<std::vector<double>> matrix, std::vector<double> bT, std::vector<double> cT);
    std::tuple<std::vector<std::vector<double>> , std::vector<double> , std::vector<double> , std::vector<int> ,std::vector<int>, double> pivot(std::vector<std::vector<double>> matrix, std::vector<double> bT, std::vector<double> cT, std::vector<int> N,std::vector<int> B, double v, int l, int e);

public:
    Simplex();
    Simplex(int n, int m);
    //Simplex(int n, int m, std::vector<std::vector<double>> matrix, std::vector<double> bT, std::vector<double> cT);

    ~Simplex();

    std::tuple<std::vector<double>, double> algorithm(std::vector<std::vector<double>> matrix, std::vector<double> bT, std::vector<double> cT);
};

#endif // SIMPLEX_H
