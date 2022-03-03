#pragma once

#include <string>
#include <vector>

#include "BinWriter.h"
#include "BinReader.h"

#include <iostream>

class Rle
{
private:

public:
    Rle() {}
    ~Rle() {}

    static void FRLE(BinWriter *&bw, std::vector<short> matrix) {
        // for (auto it : matrix) {
        //     std::cout << it << " ";
        // }

        //std::cout << std::endl;

        short zeroCounter = 0;

        bw->writeShort(matrix[0]);
        
        for (int x = 1; x < matrix.size(); x++) {
            if (matrix[x] == 0) {
                zeroCounter++;
                continue;
            }
            else {
                //rule C
                if (zeroCounter == 0) {
                    bw->writeBit(true);
                    bw->writeShort(matrix[x]);
                }
                else{
                    bw->writeBit(false);
                    bw->writeByte((char)zeroCounter);
                    bw->writeShort(matrix[x]);

                    zeroCounter = 0;
                }
            }
        }

        if (zeroCounter != 0) {
            bw->writeBit(false);
            bw->writeByte((char)zeroCounter);
        }

    }

    static std::vector<short> IRLE(BinReader *&br) {
        std::vector<short> vec;

        vec.push_back(br->readShort());

        while (vec.size() != 64) {
            bool bit = br->readBit();
            
            if (bit) {
                vec.push_back(br->readShort());
            }
            else {
                short zeroCounter = (short)br->readByte();

                for (unsigned short x = 0; x < zeroCounter; x++) {
                    vec.push_back(0);
                }

                if (vec.size() != 64) {
                    vec.push_back(br->readShort());                    
                }
            }
        }

        // for (auto it : vec) {
        //     std::cout << it << " ";
        // }

        // std::cout << std::endl;

        return vec;
    }

};
