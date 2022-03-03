#include <iostream>
#include <vector>
#include <string>
#include <sys/stat.h>
#include <exception>
#include <chrono>
#include <random>
#include <limits>

#include "Compression.h"
#include "Decompression.h"
#include "Huffman.h"

typedef std::numeric_limits< double > dbl;


bool fileExists (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}


int main(int argc, char *argv[]) {
    //std::cout.precision(dbl::max_digits10);

    if (argc != 5) {
        std::cerr << "Invalid argument count: " << argc << " != 5" << std::endl;
    }

    std::string inputFile = argv[1];
    std::string option = argv[2];
    std::string outFile = argv[3];
    unsigned int thr; 

    if (!fileExists(inputFile)) {
        std::cerr << inputFile << " does not exist." << std::endl;
        return 1;
    }

    try {
        thr = std::stoi(argv[4]);
    }
    catch (std::exception& e) {
        std::cerr << argv[4] << " is not a number." << std::endl;
        return 2;
    }

    auto start = std::chrono::steady_clock::now();

    if (option == "d") {
        Huffman *huffman = new Huffman();

        auto [newWidth, newHeight, newMaxEl, newMinEl, booleanData, newMapForHuffman] = Utils::readBinFile(inputFile);

        auto whatWeGetFromDecoding = huffman->Decode(booleanData, newMapForHuffman);

        //auto decodedData = Utils::charToOriginalData(dataToCharRes, *max_el, *min_el);
        auto decodedData = Utils::charToOriginalData(whatWeGetFromDecoding, (double)newMaxEl, (double)newMinEl);


        Decompression *decomp = new Decompression(outFile, newHeight, newWidth, decodedData);

        decomp->algorithm();


    }
    else if (option == "c") {
        Compression *comp = new Compression(inputFile, thr);

        unsigned int width, height;
        std::vector<double> data;
        
        std::tie(height, width, data) = comp->algorithm();

        Utils::applyTHR(data, thr);

        auto max_el = std::max_element(data.begin(), data.end());
        auto min_el = std::min_element(data.begin(), data.end());

        auto dataToCharRes = Utils::dataToChar(data);

        Huffman *huffman = new Huffman();

        auto [tree, cf] = huffman->Encode(dataToCharRes);

        Utils::writeBinFile(height, width, (float)*max_el, (float)*min_el, dataToCharRes, tree, cf, outFile);

        Utils::compressionFactor(inputFile, outFile);
        
    }
    else if (option == "test") {
        // std::vector<std::vector<double>> newMatrix = Utils::emptyMatrix8x8();

        // int zx = 0;
        // std::cout << std::endl;
        // for (int x = 0; x < 8; x++) {
        //     for (int y = 0; y < 8; y++) {
        //         newMatrix[x][y] = (double)zx++;
        //         std::cout << newMatrix[x][y] << "\t";
        //     }

        //     std::cout << std::endl;
        // }

        // std::vector<std::vector<double>> toTransform = HaarTransform::transform(newMatrix);




        // std::vector<double> trans = ZigZag::transform(toTransform);

        //     std::cout << std::endl;
        // for (auto el : trans) {
        //     std::cout << el << " ";
        // }
        //             std::cout << std::endl;


        // std::vector<std::vector<double>> res = ZigZag::iTransform(trans);

        // std::vector<std::vector<double>> mattt = HaarTransform::iTransform(toTransform);

        

        // std::cout << std::endl;
        // for (int x = 0; x < 8; x++) {
        //     for (int y = 0; y < 8; y++) {
        //         //v[x][y] = (double)dist(rng);
        //         std::cout << mattt[x][y] << "\t";
        //     }

        //     std::cout << std::endl;
        // }


        // std::vector<std::vector<double>> newMatrix = Utils::emptyMatrix8x8();


        // std::cout << std::endl;
        // for (int x = 0; x < 8; x++) {
        //     for (int y = 0; y < 8; y++) {
        //         newMatrix[x][y] = 0;
        //         std::cout << newMatrix[x][y] << "\t";
        //     }

        //     std::cout << std::endl;
        // }

        // std::vector<std::vector<double>> mattt = HaarTransform::transform(newMatrix);

        // std::cout << std::endl;
        // for (int x = 0; x < 8; x++) {
        //     for (int y = 0; y < 8; y++) {
        //         //v[x][y] = (double)dist(rng);
        //         std::cout << mattt[x][y] << "\t";
        //     }

        //     std::cout << std::endl;
        // }




        Compression *comp = new Compression(inputFile, thr);

        unsigned int width, height;
        std::vector<double> data;
        
        std::tie(height, width, data) = comp->algorithm();

        Utils::applyTHR(data, thr);

        auto max_el = std::max_element(data.begin(), data.end());
        auto min_el = std::min_element(data.begin(), data.end());

        auto dataToCharRes = Utils::dataToChar(data);

        Huffman *huffman = new Huffman();

        auto [tree, cf] = huffman->Encode(dataToCharRes);

        Utils::writeBinFile(height, width, (float)*max_el, (float)*min_el, dataToCharRes, tree, cf, "out_test.bin");

        auto [newHeight, newWidth, newMaxEl, newMinEl, booleanData, newMapForHuffman] = Utils::readBinFile("out_test.bin");

        auto whatWeGetFromDecoding = huffman->Decode(booleanData, newMapForHuffman);

        //auto decodedData = Utils::charToOriginalData(dataToCharRes, *max_el, *min_el);
        auto decodedData = Utils::charToOriginalData(whatWeGetFromDecoding, (double)newMaxEl, (double)newMinEl);


        Decompression *decomp = new Decompression(outFile, height, width, decodedData);

        decomp->algorithm();


        // std::vector<double> testData;
        // testData.push_back(0.5);
        // testData.push_back(1.0);
        // testData.push_back(-5.5);
        // testData.push_back(10.25);
        // testData.push_back(543.51);

        // auto dataToCharRes = Utils::dataToChar(testData);

        // auto decodedData = Utils::charToOriginalData(dataToCharRes, 543.51, -5.5);

        // for (auto el : decodedData) {
        //     std::cout << el << std::endl;
        // }
    }

    else {
        std::cerr << option << " not in [d,c]." << std::endl;
        return 3;
    }

    auto end = std::chrono::steady_clock::now();

    long time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Time to complete: " << time << "ms." << std::endl;

    return 0;
}