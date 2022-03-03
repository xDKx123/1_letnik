#pragma once

#include <vector>
#include <cmath>
#include <numbers>
#include <iostream>

class Dct
{
private:
    /* data */
public:
    Dct(/* args */) {}
    ~Dct(){}

    static std::vector<std::vector<short>> fDCT(std::vector<std::vector<short>> matrix) {
        std::vector<std::vector<short>> newMatrix;


        for (unsigned short u = 0; u < matrix.size(); u++) {
            std::vector<short> tmp;
            for (unsigned short v = 0; v < matrix[u].size(); v++) {
                double Cu = u == 0 ? 1 / std::sqrt((double)2) : 1;
                double Cv = v == 0 ? 1 / std::sqrt((double)2) : 1;
                double sum = 0.0;

                for (unsigned short x = 0; x < matrix.size(); x++) {
                    for (unsigned short y = 0; y < matrix[x].size(); y++) {
                        if (u == 0 && v == 0) {
                            sum += (double)matrix[x][y] * std::cos((double)(2*x +1) * u * M_PI / 16) * std::cos((double)(2*y + 1) * v * M_PI / 16);
                        }
                        else {
                            sum += ((double)matrix[x][y] - 128) * std::cos((double)(2*x +1) * u * M_PI / 16) * std::cos((double)(2*y + 1) * v * M_PI / 16);
                        }
                    }
                }

                tmp.push_back((short)(0.25 * Cu * Cv * sum));
            }

            newMatrix.push_back(tmp);
        }

        return newMatrix;
    }

    static std::vector<std::vector<short>> iDCT(std::vector<std::vector<short>> matrix) {
        std::vector<std::vector<short>> newMatrix;

        for (unsigned short x = 0; x < matrix.size(); x++) {
            std::vector<short> tmp;
            for (unsigned short y = 0; y < matrix[x].size(); y++) {
                double sum = 0.0;
                for (unsigned short u = 0; u < matrix.size(); u++) {
                    for (unsigned short v = 0; v < matrix[u].size(); v++) {
                        double Cu = u == 0 ? 1 / std::sqrt((double)2) : 1;
                        double Cv = v == 0 ? 1 / std::sqrt((double)2) : 1;
                        sum += Cu * Cv * ((double)matrix[u][v]) * std::cos(((double)(2*x)+1) * u * M_PI / 16) * std::cos(((double)2*y + 1) * v * M_PI /16);
                    }
                }

                tmp.push_back((short)(0.25 * sum));

                if (tmp.back() < 0) {
                    tmp.back() = 0;
                }
                if (tmp.back() > 255) {
                    tmp.back() = 255;
                }
            } 

            newMatrix.push_back(tmp);
        }

        // for (auto row : newMatrix) {
        //                 for (auto el : row) {
        //                     std::cout << el << " ";
        //                 }

        //                 std::cout << std::endl;
        //             }

        return newMatrix;
    }
};