#include "Encoding.h"
#include "Decoding.h"
#include "BinWriter.h"
#include "BinReader.h"


#include <iostream>
#include <string>
#include <chrono>

int main(int argc, char *argv[]) {
    if (argc != 7) {
        std::cerr << "Argc: 7 != " << argc << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string option = argv[2];
    std::string messageFile = argv[3];
    short N = std::stoi(argv[4]);
    short M = std::stoi(argv[5]);
    std::string outFile = argv[6];

    if (!Utils::fileExists(inputFile)) {
        std::cerr << inputFile << " does not exist" << std::endl;
        return 1;
    }


    if (option == "h") {
        Encoding *enc = new Encoding(inputFile, outFile, N,M);

        std::cout << "Running encoding" << std::endl;
        
        auto start = std::chrono::steady_clock::now();
        enc->algorithm();
        auto end = std::chrono::steady_clock::now();

        delete enc;

        std::cout << "\nCompleted in: " << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << "ms." << std::endl;
        std::cout << "Generated file: " << outFile << std::endl;

    }
    else if (option == "e") {
        Decoding *dec = new Decoding(inputFile, outFile);

        std::cout << "Running decoding" << std::endl;
        
        auto start = std::chrono::steady_clock::now();
        dec->algorithm();
        auto end = std::chrono::steady_clock::now();

        delete dec;

        std::cout << "\nCompleted in: " << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << "ms." << std::endl;
        std::cout << "Generated file: " << outFile << std::endl;        
    }
    else if (option == "test") {

        std::vector<std::vector<short>> matrix = {
            {5,5,5,5,45,45,45,45},
            {5,5,5,5,45,45,45,45},
            {5,5,5,5,45,45,45,45},
            {5,5,5,5,45,45,45,45},            
            {5,5,5,5,45,45,45,45},
            {5,5,5,5,45,45,45,45},
            {5,5,5,5,45,45,45,45},
            {5,5,5,5,45,45,45,45},
            };

        // for (int x = 0; x < 8; x++) {
        //     std::vector<short> tmp;
        //     for (int y = 0; y < 8; y++) {
        //         tmp.push_back((x+y)*y);
        //     }
        //     matrix.push_back(tmp);
        // }

        for (auto row : matrix) {
            for (auto el : row ) {
                std::cout << el << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        std::vector<std::vector<short>> dctMatrix = Dct::fDCT(matrix);

        std::vector<short> vec = Zigzag::fZigZag(dctMatrix);

        for (auto el : vec) {
            std::cout << el << " ";
        }
        std::cout << std::endl << std::endl;

        std::vector<std::vector<short>> someMat = Zigzag::iZigZag(vec);

        // for (auto row : dctMatrix) {
        //     for (auto el : row ) {
        //         std::cout << el << " ";
        //     }
        //     std::cout << std::endl;
        // }
        //             std::cout << std::endl;

        std::vector<std::vector<short>> redMatrix = Dct::iDCT(someMat);

        for (auto row : redMatrix) {
            for (auto el : row ) {
                std::cout << el << " ";
            }
            std::cout << std::endl;
        }
                    std::cout << std::endl;

        // BinWriter *bw = new BinWriter("test.bin");

        // bw->writeShort(15);
        // bw->writeShort(10);
        // bw->writeShort(4678);

        // delete bw;

        // BinReader *br = new BinReader("test.bin");

        // br->readByte();

        // std::cout << br->readShort() << std::endl;
        // std::cout << br->readShort() << std::endl;
        // std::cout << br->readShort() << std::endl;

        // delete br;

    }
    else {
        std::cerr << "Options {h, e} != " << option << std::endl;
        return 2;
    }

    


    return 0;
}