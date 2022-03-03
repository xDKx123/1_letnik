#pragma once

#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <filesystem>
#include <iostream>

#include "BinReader.h"
#include "BinWriter.h"

class Utils
{
private:
    /* data */
public:
    Utils(/* args */) {}
    ~Utils() {}

    static std::vector<std::vector<double>> emptyMatrix8x8() {
        std::vector<std::vector<double>> outMatrix;

        for (int x = 0; x < 8; x++) {
            std::vector<double> v;
            for (int y = 0; y < 8; y++) {
                v.push_back(0.0);
            }
            outMatrix.push_back(v);
        }

        return outMatrix;
    }

    static std::vector<std::vector<int>> emptyShortMatrix8x8() {
        std::vector<std::vector<int>> outMatrix;

        for (int x = 0; x < 8; x++) {
            std::vector<int> v;
            for (int y = 0; y < 8; y++) {
                v.push_back(0);
            }
            outMatrix.push_back(v);
        }

        return outMatrix;
    }

    static std::vector<std::vector<double>> haarMatrics() {
        std::vector<std::vector<double>> matrix {
            {std::sqrt((double)8/64), std::sqrt((double)8/64), 0.5, 0.0, sqrt((double)2/4), 0.0,0.0,0.0},
            {std::sqrt((double)8/64), std::sqrt((double)8/64), 0.5, 0.0, -sqrt((double)2/4), 0.0,0.0,0.0},
            {std::sqrt((double)8/64), std::sqrt((double)8/64), -0.5, 0.0, 0.0, sqrt((double)2/4),0.0,0.0},
            {std::sqrt((double)8/64), std::sqrt((double)8/64), -0.5, 0.0, 0.0, -sqrt((double)2/4),0.0,0.0},
            {std::sqrt((double)8/64), -std::sqrt((double)8/64), 0.0, 0.5, 0.0, 0.0, sqrt((double)2/4),0.0},
            {std::sqrt((double)8/64), -std::sqrt((double)8/64), 0.0, 0.5, 0.0, 0.0, -sqrt((double)2/4),0.0},
            {std::sqrt((double)8/64), -std::sqrt((double)8/64), 0.0, -0.5, 0.0, 0.0, 0.0, sqrt((double)2/4)},
            {std::sqrt((double)8/64), -std::sqrt((double)8/64), 0.0, -0.5, 0.0, 0.0, 0.0, -sqrt((double)2/4)},
        };

        return matrix;
    }

    static std::vector<std::vector<double>> transformMatrics(std::vector<std::vector<double>> matrix) {
        std::vector<std::vector<double>> outMatrix;

        for (int x = 0; x < matrix.size(); x++) {
            std::vector<double> v;
            for (int y = 0; y < matrix.size(); y++) {
                v.push_back(0.0);
            }
            outMatrix.push_back(v);
        }

        for (int x = 0; x < matrix.size(); x++) {
            for (int y = 0; y < matrix.size(); y++) {
                outMatrix[y][x] = matrix[x][y];
            }
        }

        return outMatrix;
    }

    static std::vector<std::vector<double>> multiplyMatrix(std::vector<std::vector<double>> matrix1, std::vector<std::vector<double>> matrix2) {
        std::vector<std::vector<double>> outMatrix;

        for (int x = 0; x < matrix1.size(); x++) {
            std::vector<double> v;
            for (int y = 0; y < matrix1.size(); y++) {
                v.push_back(0.0);

            }
            outMatrix.push_back(v);
        }

        for (int x = 0; x < matrix1.size(); x++) {
            for (int y = 0; y < matrix1.size(); y++) {
                for (int z = 0; z < matrix1.size(); z++) {
                    outMatrix[x][y] += matrix1[x][z] * matrix2[z][y];
                }
            }
        }

        return outMatrix;
    }

    static void applyTHR(std::vector<double> &data, unsigned int thr) {
        std::transform(data.begin(), data.end(), data.begin(), [thr](double &c){ return std::abs(c) <= thr ? 0.0 : c; });
    }

    static std::vector<unsigned char> dataToChar(std::vector<double> data) {
        auto max_el = std::max_element(data.begin(), data.end());
        auto min_el = std::min_element(data.begin(), data.end());

        std::vector<unsigned char> v;
        for (auto &el : data) {
            v.push_back((unsigned char)(((el - *min_el)/(*max_el))*256));
        }

        return v;
        //transform(data.begin(), data.end(), data.begin(), [it](int &c){ return c/(*it) * 256; });
    }

    static std::vector<double> charToOriginalData(std::vector<unsigned char> data, double max_el, double min_el) {
        std::vector<double> v;

        for (auto &el : data) {
            v.push_back((((((double)el)/256)*(max_el) + min_el)));
        }

        return v;
    }

    static std::map<unsigned char, int> commonDictionaryMap() {
        std::map<unsigned char, int> mp;
        for (int x = 0; x < 256; x++) {
            //v->push_back(static_cast<char>(x));
            mp.insert(std::pair<char, int>( static_cast<unsigned char> (x), 0));
        }
        return mp;
    }

    static void writeBinFile(int width, int height, float maxValue, float minValue, std::vector<unsigned char> items, std::map<unsigned char, std::vector<bool>> encodedValues, std::map<unsigned char, float> probability, std::string fileName)
    {
        //dodaj zapise za glavo
        //std::string fileName = "out" + validEncryptedFileExtension;
        BinWriter* binWriter = new BinWriter(fileName);

        binWriter->writeShort(width);
        binWriter->writeShort(height);

        binWriter->writeFloat(maxValue);
        binWriter->writeFloat(minValue);

        for (int x = 0; x < 256; x++) {
            if (probability.find(static_cast<char>(x)) != probability.end()) {
                binWriter->writeFloat(probability[static_cast<char>(x)]);
            }
            else {
                binWriter->writeFloat(0.0f);
            }
        }




        //for (auto pair : probability) {
        //	//binWriter->writeByte(pair.first);
        //	binWriter->writeFloat(probability[pair]);
        //}

        for (auto item : items) {
            for (auto v : encodedValues[item]) {
                binWriter->writeBit(v);
            }
        }

        for (int x = 0; x < 7; x++) {
            binWriter->writeBit(false);
        }
        binWriter->writeBit(true);

        std::cout << "Ustvarjan dokument: " << fileName << std::endl;

        delete binWriter;
    }


    static std::tuple<int, int, float, float, std::vector<bool>, std::map<unsigned char, float>> readBinFile(std::string fileName)
    {
        //NE DIRAJ KER DELA
        //std::string fileName = getImage();
        //std::string fileName = "out.bin";
        BinReader* binReader = new BinReader(fileName);

        for (int x = 0; x < 8; x++) {
            binReader->readBit();
        }

        int width = binReader->readShort();
        int height = binReader->readShort();

        float maxValue = binReader->readFloat();
        float minValue = binReader->readFloat();

        std::map<unsigned char, float> probability;
        //int probabilitySize = binReader->readInt();
        //std::cout << "probabilitySize: " << probabilitySize << std::endl;
        for (int x = 0; x < 256; x++) {
            //char c = binReader->readByte();
            float f = binReader->readFloat();
            if (f != 0.0f) {
                probability.insert(std::pair<unsigned char, float>(static_cast<unsigned char>(x),f));
            }
        }

        std::vector<bool> data;

        while (!binReader->isEof()) {
            data.push_back(binReader->readBit());
        }

        while (data.back() != true) {
            data.pop_back();
        }

        for (int x = 0; x < 8; x++) {
            data.pop_back();
        }

        delete binReader;

        return std::tuple<int, int, float, float, std::vector<bool>, std::map<unsigned char, float>>(width, height, maxValue, minValue, data, probability);
    }

    static void compressionFactor(std::string originalFile, std::string compressedFile) {
        std::filesystem::path originalPath{originalFile};
        std::filesystem::path compressedPath{compressedFile};

        std::cout << "Compression factor: " << (double)std::filesystem::file_size(originalPath) / (double)std::filesystem::file_size(compressedFile) << std::endl;
    }
};
