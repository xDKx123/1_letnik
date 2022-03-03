#pragma once

#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>

#include "Utils.h"
#include "Dct.h"
#include "Zigzag.h"
#include "Rle.h"
#include "BinWriter.h"

#include <string>
#include <iostream>

class Encoding
{
private:
    /* data */
    cv::Mat image;
    BinWriter *bw;
    short N;
    short M;
    
public:
    Encoding(std::string(fileName), std::string outFile, short N, short M) : image(Utils::readImage(fileName)), N(N), M(M) {
         bw = new BinWriter(outFile);
    }
    ~Encoding() {
        delete bw;
    }

    void algorithm() {
        int height = image.size().height;
        int width = image.size().width;

        bw->writeInt(height);
        bw->writeInt(width);
        bw->writeShort(N);
        bw->writeShort(M);


        unsigned int operations = 0;
        

        for (unsigned int x = 0; x < height; x+=8) {
            for (unsigned int y = 0; y < width; y+=8) {
                for (unsigned short z = 0; z < 3; z++, operations++) {
                    std::vector<std::vector<short>> matrix = Utils::get8x8vector(image, x, x+8 > height ? height : x+8, y, y+8 > width ? width : y+8, z);
                
                    std::vector<std::vector<short>> dctMatrix = Dct::fDCT(matrix);

                    std::vector<short> vec = Zigzag::fZigZag(matrix);

                    Rle::FRLE(bw, vec);

                    Utils::printProgress((double)operations /  (((height*width *3) / 64) -1));
                }
            }
        }
    }
};