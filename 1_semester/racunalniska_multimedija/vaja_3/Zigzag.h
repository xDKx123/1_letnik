#pragma once

#include <vector>

class Zigzag
{
private:
    /* data */
public:
    Zigzag(/* args */) {}
    ~Zigzag() {}


    static std::vector<short> fZigZag(std::vector<std::vector<short>> matrix){
        std::vector<short> vec;

        vec.push_back(matrix[0][0]);
        vec.push_back(matrix[0][1]);

        int indexX = 0;
        int indexY = 1;

        bool way = true;

        while (vec.size() != 64) {
            if (way) {
                while (indexY != 0 && indexX != 7) {
                    vec.push_back(matrix[++indexX][--indexY]);
                }

                vec.push_back(indexX == 7 ? matrix[indexX][++indexY] : matrix[++indexX][indexY]);
            }
            else {
                while (indexY != 7 && indexX != 0) {
                    vec.push_back(matrix[--indexX][++indexY]);
                }

                vec.push_back(indexY == 7 ? matrix[++indexX][indexY] : matrix[indexX][++indexY]);
            }

            way = !way;
        }

        return vec;
    }

    static std::vector<std::vector<short>> iZigZag(std::vector<short> vec) {
        std::vector<std::vector<short>> matrix;

        for (unsigned short x = 0; x < 8; x++) {
            std::vector<short> tmp;
            for (unsigned short y = 0; y < 8; y++) {
                tmp.push_back(0);
            }
            matrix.push_back(tmp);
        }

        matrix[0][0] = vec[0];
        matrix[0][1] = vec[1];

        int indexX = 0;
        int indexY = 1;
        bool way = true;

        int index = 2;

        while (index < 64) {
            if (way) {
                while (indexY != 0 && indexX != 7) {
                    matrix[++indexX][--indexY] = vec[index++];
                }

                if (indexX == 7) {
                    matrix[indexX][++indexY] = vec[index++];
                }
                else {
                    matrix[++indexX][indexY] = vec[index++];
                }
            }
            else {
                while (indexY != 7 && indexX != 0) {
                    matrix[--indexX][++indexY] = vec[index++];
                }

                if (indexY == 7) {
                    matrix[++indexX][indexY] = vec[index++];
                }
                else {
                    matrix[indexX][++indexY] = vec[index++];
                }
            }

            way = !way;
        }
        return matrix;
    }
};