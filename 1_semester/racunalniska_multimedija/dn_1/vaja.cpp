#include <iostream>
#include <vector>
#include <bitset>
#include  <sstream>

#include "BinReader.h"
#include "BinWriter.h"

//write bits to file
//read 8 bits and create char with std::bitset
void write_bits(std::vector<bool> bits, std::string fileName) {
    BinWriter *bw = new BinWriter(fileName);

    std::string bitStr = "";
    for (auto b : bits) {
        bitStr.push_back(b == true ? '1' : '0');

        if (bitStr.size() == 8) {
            char c = static_cast<char>(std::bitset<8>(bitStr).to_ulong());
            bw->writeByte(c);
            bitStr = "";
        }
    }

    if (bitStr.size() != 8) {
        while (bitStr.size() <= 8) {
            bitStr.push_back('0');
        }
        char c = static_cast<char>(std::bitset<8>(bitStr).to_ulong());
        bw->writeByte(c);
    }

    delete bw;
}

//read file as string.
//convert each character to binary string;
std::vector<bool> read_bits(std::string fileName) {
    BinReader *br = new BinReader(fileName);
    std::vector<bool> content;

    std::ifstream t(fileName);
    std::stringstream buffer;
    buffer << t.rdbuf();

    for (char c : buffer.str()) {

        std::string binaryChar = std::bitset<8>(c).to_string();

        for (char symbol: binaryChar) {
            content.push_back(symbol == '1');
        }

    }


    delete br;
    return content;
}

//Brute-force method for checking if string contains substring of bool
bool isSubstring(std::vector<bool> bits, std::vector<bool> subString, int position) {
    for (auto bit : subString) {
        if (bits[position] != bit) {
            return false;
        }
        position++;
    }

    return true;
}

//print every occurance, starting with index = 0;
void findInFile(std::vector<bool> bits, std::vector<bool> subString) {
    for (unsigned long x = 0; x < bits.size() - subString.size(); x++) {
        if (isSubstring(bits, subString, x)) {
            std::cout << x << " ";
        }
    }

    std::cout << std::endl;
}

//if we found a substring of bool, we replace it with new string of bool.
//if position found, we move to new position in subString, which is len of substring, not replacment.
std::vector<bool> replaceInFile(std::vector<bool> bits, std::vector<bool> subString, std::vector<bool> replacemet) {
    std::vector<bool> newBits;

    for (int x = 0; x < bits.size(); x++) {
        if (isSubstring(bits, subString, x)) {
            for (auto bit : replacemet) {
                newBits.push_back(bit);
            }
            x+=(subString.size() - 1);
        }
        else {
            newBits.push_back(bits[x]);
        }

    }

    return newBits;
}

//input binary string to vector bool.
std::vector<bool> stringToBits(std::string str) {
    std::vector<bool> bits;

    for (auto c : str) {
            
        bits.push_back(c == '1');
        
    }

    return bits;
}


int main(int argc, char *argv[]) {

    std::string fileName = std::string(argv[1]);
    std::string opt = std::string(argv[2]);

    if (opt == "f") {

        std::vector<bool> bits = read_bits(fileName);
        
        findInFile(bits, stringToBits(std::string(argv[3])));

    }
    else if (opt == "fr") {
        std::vector<bool> bits = read_bits(fileName);
        std::vector<bool> newBits = replaceInFile(bits, stringToBits(std::string(argv[3])), stringToBits(std::string(argv[4])));

        write_bits(newBits, "newFile.bin");
    }
    else {
        std::cerr << "Invalid args" << std::endl;
    }

    return 0;
}