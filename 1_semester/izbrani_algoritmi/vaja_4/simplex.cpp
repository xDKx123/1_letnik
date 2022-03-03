#include "simplex.h"

#include <string>

Simplex::Simplex() {

}

//Simplex::Simplex(int n, int m, std::vector<std::vector<double>> matrix, std::vector<double> bT, std::vector<double> cT) : n(n), m(m), matrix(matrix), bT(bT), cT(cT)
//{

//}

Simplex::Simplex(int n, int m) : n(n), m(m) {

}

Simplex::~Simplex() {  }

//Private methods
std::tuple<std::vector<int>,std::vector<int>, double> Simplex::initialize(std::vector<std::vector<double>> matrix, std::vector<double> bT, std::vector<double> cT) {
    if (*std::min_element(bT.begin(), bT.end()) >= 0) {
        std::vector<int> N, B;
        double v;

        for (int x = 0; x < n; x++) {
            N.push_back(x);
        }

        for (int x = n; x < n + m; x++) {
            B.push_back(x);
        }

        v = 0.0;

        return {N,B,v};
    }

    throw std::string("b must contain values above 0");
}

std::tuple<std::vector<std::vector<double>> , std::vector<double> , std::vector<double> , std::vector<int> ,std::vector<int>, double> Simplex::pivot(std::vector<std::vector<double>> matrix, std::vector<double> bT, std::vector<double> cT, std::vector<int> N,std::vector<int> B, double v, int l, int e) {
    auto n_a = Utils::empty2Dmatrix(matrix);
    auto n_bT = Utils::empty1Dmatrix(bT);
    auto n_cT = Utils::empty1Dmatrix(cT);
    auto n_N = Utils::copy1Dmatrix(N);
    auto n_B = Utils::copy1Dmatrix(B);



    n_bT[e] = bT[l] / matrix[l][e];

    for (unsigned int j = 0; j < N.size(); j++) {
        if (N[j] != e) {
            n_a[e][N[j]] = matrix[l][N[j]]/matrix[l][e];
        }
    }
    n_a[e][l] = 1/matrix[l][e];

    for (unsigned int i = 0; i < B.size(); i++) {
        if (B[i] != l ) {
            n_bT[B[i]] = bT[B[i]] - matrix[B[i]][e]*n_bT[e];
        }
        for (unsigned int j = 0; j < N.size(); j++) {
            if (N[j] != e) {
                n_a[B[i]][N[j]] = matrix[B[i]][N[j]] - matrix[B[i]][e]*n_a[e][N[j]];
            }
            n_a[B[i]][l] = -matrix[B[i]][e] * n_a[e][l];
        }
    }

    double n_v = v + cT[e]*n_bT[e];

    for (unsigned int j = 0; j < N.size(); j++) {
        if (N[j] != e) {
            n_cT[N[j]] = cT[N[j]] - cT[e]*n_a[e][N[j]];
        }
    }
    n_cT[l] = -cT[e] * n_a[e][l];

    for (unsigned int x = 0 ; x < n_N.size(); x++) {
        if (N[x] == e) {
            n_N[x] = l;
            break;
        }
    }

    for (unsigned int x = 0 ; x < n_B.size(); x++) {
        if (B[x] == l) {
            n_B[x] = e;
            break;
        }
    }

    std::sort(n_N.begin(), n_N.end());
    std::sort(n_B.begin(), n_B.end());

    return {n_a, n_bT, n_cT, n_N, n_B, n_v};
}

std::tuple<std::vector<double>, double> Simplex::algorithm(std::vector<std::vector<double>> matrix, std::vector<double> bT, std::vector<double> cT) {
    auto [N,B,v] = initialize(matrix, bT, cT);

    while (*std::max_element(cT.begin(), cT.end()) > 0) {
        std::vector<double>::iterator it = std::find_if(cT.begin(), cT.end(), [](const double & val) {return val > 0;});

        int e = std::distance(cT.begin(), it);

        std::vector<double> diff;
        for (unsigned int x = 0; x < bT.size(); x++) {
            if (matrix[x][e] > 0) {
                diff.push_back(bT[x] / matrix[x][e]);
            }
            else {
                diff.push_back(infinity);
            }
        }

        std::vector<double>::iterator it2 = std::min_element(diff.begin(), diff.end());

        if (*it2 == infinity) {
            throw std::string("Infinity program.");
        }

        int l = std::distance(diff.begin(), it2);

        auto [newMatrix, n_bT, n_cT, n_N, n_B ,n_v] = pivot(matrix, bT, cT, N, B, v, l, e);

        matrix = Utils::copy2Dmatrix(newMatrix);
        bT = Utils::copy1Dmatrix(n_bT);
        cT = Utils::copy1Dmatrix(n_cT);
        N = Utils::copy1Dmatrix(n_N);
        B= Utils::copy1Dmatrix(n_B);
        v = n_v;
    }

    return {bT, v};
}
