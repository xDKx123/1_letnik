#pragma once

#include <string.h>
#include <vector>
#include <iostream>

#include "BinReader.h"
#include "Utils.h"
#include "Rle.h"
#include "Zigzag.h"
#include "Dct.h"

#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>

class Decoding
{
private:
    std::string outFile;
    BinReader *br;

    void insertToImage(cv::Mat &image, unsigned int startX,unsigned int endX,unsigned int startY,unsigned int endY, std::vector<std::vector<short>> redMatrix, std::vector<std::vector<short>> greenMatrix, std::vector<std::vector<short>> blueMatrix) {
        for (unsigned int x = startX; x < endX; x++) {
            for (unsigned int y = startY; y < endY; y++) {
                cv::Vec3b pixel;

                //std::cout << "before creating pixel" << std::endl;

                pixel[0] = redMatrix[x-startX][y-startY];
                pixel[1] = greenMatrix[x-startX][y-startY];
                pixel[2] = blueMatrix[x-startX][y-startY];

                //std::cout << "pixel created" << std::endl;
                
                image.at<cv::Vec3b>(x, y) = pixel;
            }
        }
    }

public:
    Decoding(std::string inputFile, std::string outFile) : outFile(outFile) {
        br = new BinReader(inputFile);
        br->readByte();
    }
    ~Decoding() {
        delete br;
    }

    void algorithm() {

        //std::cout << "is here 1" << std::endl;

        int height = br->readInt();
        int width = br->readInt();
        int N = br->readShort();
        int M = br->readShort();


        //std::cout << height << " " << width << " " << N << " " << M << std::endl;

        //std::cout << "is here 2" << std::endl;
        cv::Mat image = cv::Mat(cv::Size(width, height), CV_8UC3);


        unsigned int operations = 0;

        for (unsigned int x = 0; x < height; x+=8) {
            for (unsigned int y = 0; y < width; y+=8) {
                std::vector<std::vector<short>> redMatrix;
                std::vector<std::vector<short>> greenMatrix;
                std::vector<std::vector<short>> blueMatrix;

                for (short z = 0; z < 3; z++, operations++) {
                    // std::cout << "Begin" << std::endl;  
                    std::vector<short> vec = Rle::IRLE(br);

                    std::vector<std::vector<short>> matrix = Zigzag::iZigZag(vec);

                    //std::cout << "After zigzag" << std::endl;

                    if (z == 0) {
                        redMatrix = Dct::iDCT(matrix);
                        // for (auto row : redMatrix) {
                        //     for (auto el : row) {
                        //         std::cout << el << " ";
                        //     }

                        //     std::cout << std::endl;
                        // }
                    }
                    else if (z == 1) {
                        greenMatrix = Dct::iDCT(matrix);
                    }
                    else if (z == 2) {
                        blueMatrix = Dct::iDCT(matrix);
                    }
                }

                // for (auto row : redMatrix) {
                //     for (auto el : row) {
                //         std::cout << el << " ";
                //     }

                //     std::cout << std::endl;
                // }

                insertToImage(image, x, x+8 > height ? height : x+8, y, y+8 > width ? width : y+8, redMatrix, greenMatrix, blueMatrix);

                //std::cout << "After inserting to image" << std::endl;

                Utils::printProgress((double)operations /  (((height*width *3) / 64) -1));
            }
        }

        Utils::writeImage(outFile, image);
    }
};