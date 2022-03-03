#pragma once

#include <vector>
#include <cmath>

class ZigZag
{
private:
    /* data */
public:
    ZigZag(/* args */);
    ~ZigZag();

    static std::vector<double> transform(std::vector<std::vector<double>> matrix);
    static std::vector<std::vector<double>> iTransform(std::vector<double> arr);
};

ZigZag::ZigZag(/* args */)
{
}

ZigZag::~ZigZag()
{
}

std::vector<double> ZigZag::transform(std::vector<std::vector<double>> matrix) {
    //         std::cout << std::endl;
    // for (auto x : matrix) {
    //     for (auto y : x) {
    //         std::cout << y << " ";
    //     }
    //     std::cout << std::endl;
    // }
    //         std::cout << std::endl;


    std::vector<double> arr;

    arr.push_back(matrix[0][0]);
    arr.push_back(matrix[0][1]);
    arr.push_back(matrix[1][0]);
    arr.push_back(matrix[2][0]);
    arr.push_back(matrix[1][1]);
    arr.push_back(matrix[0][2]);
    arr.push_back(matrix[0][3]);
    arr.push_back(matrix[1][2]);

    arr.push_back(matrix[2][1]);
    arr.push_back(matrix[3][0]);
    arr.push_back(matrix[4][0]);
    arr.push_back(matrix[3][1]);
    arr.push_back(matrix[2][2]);
    arr.push_back(matrix[1][3]);
    arr.push_back(matrix[0][4]);
    arr.push_back(matrix[0][5]);

    arr.push_back(matrix[1][4]);
    arr.push_back(matrix[2][3]);
    arr.push_back(matrix[3][2]);
    arr.push_back(matrix[4][1]);
    arr.push_back(matrix[5][0]);
    arr.push_back(matrix[6][0]);
    arr.push_back(matrix[5][1]);
    arr.push_back(matrix[4][2]);

    arr.push_back(matrix[3][3]);
    arr.push_back(matrix[2][4]);
    arr.push_back(matrix[1][5]);
    arr.push_back(matrix[0][6]);
    arr.push_back(matrix[0][7]);
    arr.push_back(matrix[1][6]);
    arr.push_back(matrix[2][5]);
    arr.push_back(matrix[3][4]);

    arr.push_back(matrix[4][3]);
    arr.push_back(matrix[5][2]);
    arr.push_back(matrix[6][1]);
    arr.push_back(matrix[7][0]);
    arr.push_back(matrix[7][1]);
    arr.push_back(matrix[6][2]);
    arr.push_back(matrix[5][3]);
    arr.push_back(matrix[4][4]);

    arr.push_back(matrix[3][5]);
    arr.push_back(matrix[2][6]);
    arr.push_back(matrix[1][7]);
    arr.push_back(matrix[2][7]);
    arr.push_back(matrix[3][6]);
    arr.push_back(matrix[4][5]);
    arr.push_back(matrix[5][4]);
    arr.push_back(matrix[6][3]);

    arr.push_back(matrix[7][2]);
    arr.push_back(matrix[7][3]);
    arr.push_back(matrix[6][4]);
    arr.push_back(matrix[5][5]);
    arr.push_back(matrix[4][6]);
    arr.push_back(matrix[3][7]);
    arr.push_back(matrix[4][7]);
    arr.push_back(matrix[5][6]);

    arr.push_back(matrix[6][5]);
    arr.push_back(matrix[7][4]);
    arr.push_back(matrix[7][5]);
    arr.push_back(matrix[6][6]);
    arr.push_back(matrix[5][7]);
    arr.push_back(matrix[6][7]);
    arr.push_back(matrix[7][6]);
    arr.push_back(matrix[7][7]);

    return arr;


}

std::vector<std::vector<double>> ZigZag::iTransform(std::vector<double> arr) {
    std::vector<std::vector<double>> matrix = Utils::emptyMatrix8x8();

    matrix[0][0] = arr[0];
    matrix[0][1] = arr[1];
    matrix[1][0] = arr[2];
    matrix[2][0] = arr[3];
    matrix[1][1] = arr[4];
    matrix[0][2] = arr[5];
    matrix[0][3] = arr[6];
    matrix[1][2] = arr[7];

    matrix[2][1] = arr[8];
    matrix[3][0] = arr[9];
    matrix[4][0] = arr[10];
    matrix[3][1] = arr[11];
    matrix[2][2] = arr[12];
    matrix[1][3] = arr[13];
    matrix[0][4] = arr[14];
    matrix[0][5] = arr[15];

    matrix[1][4] = arr[16];
    matrix[2][3] = arr[17];
    matrix[3][2] = arr[18];
    matrix[4][1] = arr[19];
    matrix[5][0] = arr[20];
    matrix[6][0] = arr[21];
    matrix[5][1] = arr[22];
    matrix[4][2] = arr[23];

    matrix[3][3] = arr[24];
    matrix[2][4] = arr[25];
    matrix[1][5] = arr[26];
    matrix[0][6] = arr[27];
    matrix[0][7] = arr[28];
    matrix[1][6] = arr[29];
    matrix[2][5] = arr[30];
    matrix[3][4] = arr[31];

    matrix[4][3] = arr[32];
    matrix[5][2] = arr[33];
    matrix[6][1] = arr[34];
    matrix[7][0] = arr[35];
    matrix[7][1] = arr[36];
    matrix[6][2] = arr[37];
    matrix[5][3] = arr[38];
    matrix[4][4] = arr[39];

    matrix[3][5] = arr[40];
    matrix[2][6] = arr[41];
    matrix[1][7] = arr[42];
    matrix[2][7] = arr[43];
    matrix[3][6] = arr[44];
    matrix[4][5] = arr[45];
    matrix[5][4] = arr[46];
    matrix[6][3] = arr[47];

    matrix[7][2] = arr[48];
    matrix[7][3] = arr[49];
    matrix[6][4] = arr[50];
    matrix[5][5] = arr[51];
    matrix[4][6] = arr[52];
    matrix[3][7] = arr[53];
    matrix[4][7] = arr[54];
    matrix[5][6] = arr[55];

    matrix[6][5] = arr[56];
    matrix[7][4] = arr[57];
    matrix[7][5] = arr[58];
    matrix[6][6] = arr[59];
    matrix[5][7] = arr[60];
    matrix[6][7] = arr[61];
    matrix[7][6] = arr[62];
    matrix[7][7] = arr[63];

    return matrix;
}