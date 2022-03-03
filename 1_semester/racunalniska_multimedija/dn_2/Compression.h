#pragma once

#include <iostream>
#include <vector>
#include <set>

#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>

#include "Utils.h"
#include "HaarTransform.h"
#include "ZigZag.h"

class Compression
{
private:
    /* data */
    cv::Mat image;
    unsigned int thr;
    std::vector<std::vector<double>> getSubMatrix();
    bool isImage();
public:
    Compression(std::string fileName, unsigned int thr);

    ~Compression();

    std::tuple<unsigned int, unsigned int, std::vector<double>> algorithm();
};

std::vector<std::vector<double>> Compression::getSubMatrix() {
    std::vector<std::vector<double>> matrix;

    return matrix;
}

Compression::Compression(std::string fileName, unsigned int thr) : image(cv::imread(fileName)), thr(thr) {

}

Compression::~Compression() {
    
}


std::tuple<unsigned int, unsigned int, std::vector<double>> Compression::algorithm() {
    std::vector<double> result;

    for (unsigned int x = 0; x < image.size().height; x+=8) {
        for (unsigned int y = 0; y < image.size().width; y+=8) {

            for (unsigned short z = 0; z < 3; z++) {
                std::vector<std::vector<double>> matrix = Utils::emptyMatrix8x8();

                for (unsigned int u = 0; u < 8 && u + x < image.size().height; u++) {
                    for (unsigned int w = 0; w < 8 && w + y < image.size().width; w++) {

                        cv::Vec3b currentPixel = image.at<cv::Vec3b>(x + u, y + w);

                        matrix[u][w] = currentPixel[z];
                    }
                }

                //Apply har transform on given 8x8 matrix
                std::vector<std::vector<double>> transformedMatrix = HaarTransform::transform(matrix);

                // std::cout << "Haar transform" << std::endl;
                // for (auto row : transformedMatrix) {
                //     for (auto col : row) {
                //         std::cout << col << " ";
                //     }
                //     std::cout <<std::endl;
                // }
                // std::cout <<std::endl;


                std::vector<double> zigZagTransformed = ZigZag::transform(transformedMatrix);
                // std::cout << "zigZag" << std::endl;
                // for (auto row : zigZagTransformed) {
                //     std::cout << row << " ";
                // }
                // std::cout <<std::endl;



                for (auto el : zigZagTransformed) {
                    result.push_back(el);
                }
            }
        }
    }

    //std::cout << *std::max_element(std::begin(result), std::end(result)) << std::endl;

    // std::cout << "Number of unique elements is "
    //           << std::set<double>( result.begin(), result.end() ).size()
    //           << std::endl;

    // std::cout << "Max element: " << *std::max_element(result.begin(), result.end()) << std::endl;
    // std::cout << "Min element: " << *std::min_element(result.begin(), result.end()) << std::endl;

    return {image.size().height, image.size().width, result};
}