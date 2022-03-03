#include <iostream>

#include "ArithmeticCoding.h"
#include "FrequencyTable.h"
#include "Node.h"
#include "Utility.h"

int main(int argc, char* argv[]) {
    std::vector<unsigned char> data;
    data.push_back('g');
    data.push_back('e');
    data.push_back('m');
    data.push_back('m');
    data.push_back('a');

    int bitSize = 8;

    ArithmeticCoding *ac = new ArithmeticCoding(data, bitSize);
    std::vector<bool> out = ac->Encode();
    FrequencyTable* frTable = ac->getFrequencyTable();
    
    Utility::writeD("out.bin", frTable, out, bitSize);
    for (auto b : out) {
        std::cout << b;
    }

    // std::cout << std::endl;

    // FrequencyTable* freqTable;
    // std::vector<bool> data;
    // unsigned short bitSize;

    std::cout << "Binary output" << std::endl;
    
    auto [freqTable, data2, bitSize2] = Utility::readD("out.bin"); 

    // std::cout << freqTable->toString() <<std::endl;
    // for (auto element : data2) {
    //     std::cout << element;
    // }
    
    // std::cout << std::endl;

    // std::cout << bitSize2 << std::endl;

    ArithmeticCoding *acDecode = new ArithmeticCoding(freqTable, data2, bitSize2);

    auto decoded = acDecode->Decode();

    for (auto c : decoded) {
        std::cout << c;
    }
    std::cout << std::endl;

    return 0;
}