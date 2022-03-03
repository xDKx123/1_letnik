#pragma once

#define PBSTR "...................................................................................................."
#define PBWIDTH 100

#include <string>
#include <filesystem>

#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>

class Utils
{
private:
    /* data */
public:
    Utils(/* args */) {}
    ~Utils() {}

    static cv::Mat readImage(std::string fileName) {
        return cv::imread(fileName);
    }

    static void writeImage(std::string fileName, cv::Mat image) {
        cv::imwrite(fileName, image);
    }

    static std::vector<std::vector<short>> get8x8vector(cv::Mat image, unsigned int startX,unsigned int endX, unsigned int startY, unsigned int endY, unsigned short option) {
        std::vector<std::vector<short>> matrix;

        for (unsigned int x = 0; x < 8; x++) {
            std::vector<short> tmp;
            for (unsigned int y = 0; y < 8; y++) {
                tmp.push_back(0);
            }

            matrix.push_back(tmp);
        }


        for (unsigned int x = startX; x < endX; x++) {
            for (unsigned int y = startY; y < endY; y++) {
                cv::Vec3b pixel = image.at<cv::Vec3b>(x,y);


                //if (option = 0) {
                    matrix[x-startX][y-startY] = pixel[option];
                //}
            }
        }

        return matrix;
    }

    static void printProgress(double percentage) {
        int val = (int) (percentage * 100);
        int lpad = (int) (percentage * PBWIDTH);
        int rpad = PBWIDTH - lpad;
        printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
        fflush(stdout);
    }

    static bool fileExists(std::string fileName) {
        return std::filesystem::exists(fileName);
    }
};
