#pragma once

#include <string>
#include <vector>
#include <tuple>

#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>

#include "ZigZag.h"
#include "HaarTransform.h"

class Decompression
{
private:

    std::string fileName;
    unsigned int height;
    unsigned int width;
    std::vector<double> data;
    std::vector<double> subVector(int position);

public:
    Decompression(std::string fileName, unsigned int height, unsigned int width, std::vector<double> data);
    ~Decompression();

    void algorithm();
};

std::vector<double> Decompression::subVector(int position) {
    std::vector<double>::const_iterator it = data.begin() + position;
    return std::vector<double>(it, it + 64);
}

Decompression::Decompression(std::string fileName, unsigned int height, unsigned int width, std::vector<double> data) : fileName(fileName), height(height), width(width), data(data)
{
}

Decompression::~Decompression()
{
}

void Decompression::algorithm() {
    cv::Mat image = cv::Mat(cv::Size(width, height), CV_8UC3);
    int positionSubvector = 0;

    //std::cout << "\nDECOMPRESSION\n" <<std::endl;

    for (unsigned int x = 0; x < height; x+=8) {
        for (unsigned int y = 0; y < width; y+=8) {
            std::vector<std::vector<double>> matrixRed;
            std::vector<std::vector<double>> matrixGreen;
            std::vector<std::vector<double>> matrixBlue;

            for (unsigned short z = 0; z < 3; z++, positionSubvector+=64) {
                std::vector<double> v = subVector(positionSubvector);

                // std::cout << "before iZigazag" << std::endl;
                // for (auto row : v) {
                //     std::cout << row <<" ";
                // }
                // std::cout <<std::endl;

                std::vector<std::vector<double>> zigZagTransformed = ZigZag::iTransform(v);
                // std::cout << "iZigZag" << std::endl;
                // for (auto row : zigZagTransformed) {
                //     for (auto col : row) {
                //         std::cout << col << " ";
                //     }
                //     std::cout <<std::endl;
                // }
                // std::cout <<std::endl;

                if (z == 0) {
                    matrixBlue = HaarTransform::iTransform(zigZagTransformed);

                    // std::cout << "iHaar" << std::endl;
                    // for (auto row : matrixBlue) {
                    //     for (auto col : row) {
                    //         std::cout << col << " ";
                    //     }
                    //     std::cout <<std::endl;
                    // }
                    // std::cout <<std::endl;

                }
                else if (z == 1) {
                    matrixGreen = HaarTransform::iTransform(zigZagTransformed);
                    // std::cout << "iHaar" << std::endl;
                    // for (auto row : matrixGreen) {
                    //     for (auto col : row) {
                    //         std::cout << col << " ";
                    //     }
                    //     std::cout <<std::endl;
                    // }
                    // std::cout <<std::endl;
                }
                else if (z == 2) {
                    matrixRed = HaarTransform::iTransform(zigZagTransformed);
                    // std::cout << "iHaar" << std::endl;
                    // for (auto row : matrixBlue) {
                    //     for (auto col : row) {
                    //         std::cout << col << " ";
                    //     }
                    //     std::cout <<std::endl;
                    // }
                    // std::cout <<std::endl;
                }
            }

            for (unsigned int u = 0; u < 8 && u + x < height; u++) {
                for (unsigned int w = 0; w < 8 && w + y < width; w++) {
                    cv::Vec3b currentPixel;

                    for (unsigned short z = 0; z < 3; z++) {

                        if (z == 0) {
                            currentPixel[z] = (unsigned char)matrixBlue[u][w];
                        }
                        else if (z == 1) {
                            currentPixel[z] = (unsigned char)matrixGreen[u][w];
                        }
                        else if (z == 2) {
                            currentPixel[z] = (unsigned char)matrixRed[u][w];
                        }
                    }

                    image.at<cv::Vec3b>(u + x, w + y) = currentPixel;
                }
            } 
        }
    }

    cv::imwrite(fileName, image);
}