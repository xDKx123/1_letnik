#pragma once

#include <iostream>
#include <math.h>
#include <vector>

#include "FrequencyTable.h"

class ArithmeticCoding
{
private:
    FrequencyTable *frequencyTable;
    std::vector<unsigned char> data;
    std::vector<bool> binaryData;
    unsigned int globalIntervalBit;

    unsigned int calcStep(unsigned int lowerEdge, unsigned int upperEdge, unsigned int frequency);

public:
    ArithmeticCoding();
    ArithmeticCoding(std::vector<unsigned char> data, unsigned int globalIntervalBit);
    ArithmeticCoding(FrequencyTable *frequencyTable, std::vector<bool> data, unsigned int globalIntervalBit);
    ~ArithmeticCoding();

    FrequencyTable* getFrequencyTable();

    unsigned int fromVector(std::vector<bool> vec);

    std::vector<bool> Encode();
    std::vector<char> Decode();
};

unsigned int ArithmeticCoding::calcStep(unsigned int lowerEdge, unsigned int upperEdge, unsigned int frequency) {
        return std::floor((upperEdge - lowerEdge + 1) / static_cast<double>(frequency));
}

ArithmeticCoding::ArithmeticCoding()
{

}

ArithmeticCoding::ArithmeticCoding(std::vector<unsigned char> data, unsigned int globalIntervalBit) : data(data), frequencyTable(new FrequencyTable(data)), globalIntervalBit(globalIntervalBit)
{
    
}

ArithmeticCoding::ArithmeticCoding(FrequencyTable *frequencyTable, std::vector<bool> data, unsigned int globalIntervalBit) : frequencyTable(frequencyTable), binaryData(data), globalIntervalBit(globalIntervalBit) {}


ArithmeticCoding::~ArithmeticCoding()
{
}

FrequencyTable* ArithmeticCoding::getFrequencyTable() {
    return frequencyTable;
}

unsigned int ArithmeticCoding::fromVector(std::vector<bool> vec){
	unsigned int retval = 0;
	int i =0;
	for (std::vector<bool>::reverse_iterator it = vec.rbegin(); it != vec.rend(); it++,i++){
		if(*it){
			retval |= 1<<i;
		}
	}
	return retval;
}

std::vector<bool> ArithmeticCoding::Encode() {
    unsigned int lowerEdge = 0;
    unsigned int upperEdge = pow(2,globalIntervalBit-1)-1;
    unsigned int seccondQuarter = static_cast<unsigned int>(std::floor(static_cast<double>((upperEdge +1)) / 2));
    unsigned int firstQuarter = std::floor(seccondQuarter/2);
    unsigned int thirdQuarter = std::floor(firstQuarter * 3);

    std::cout << frequencyTable->toString() << std::endl;

    std::vector<bool> out;

    unsigned int counterE3 = 0;

    for (auto element : data) {
        unsigned int step = calcStep(lowerEdge, upperEdge, data.size());

        upperEdge = lowerEdge + step * frequencyTable->upperEdge(element) -1;
        lowerEdge = lowerEdge + step * frequencyTable->lowerEdge(element);
    
        while (upperEdge < seccondQuarter || lowerEdge >= seccondQuarter) {
            if (upperEdge < seccondQuarter) {
                //E1
                lowerEdge*=2;
                upperEdge= upperEdge * 2 +1;
                out.push_back(0);

                for (counterE3; counterE3 >0; counterE3--) {
                    out.push_back(1);
                }
            }
            if(lowerEdge >= seccondQuarter) {

                //E2
                
                lowerEdge = 2*(lowerEdge - seccondQuarter);
                upperEdge = 2*(upperEdge - seccondQuarter) +1;
                out.push_back(1);
                
                for (counterE3; counterE3 >0; counterE3--) {
                    out.push_back(0);
                }
            }
        }

        while(lowerEdge >= firstQuarter && upperEdge < thirdQuarter) {
            lowerEdge = 2*(lowerEdge - firstQuarter);
            upperEdge = 2*(upperEdge - firstQuarter) +1;
            counterE3++;
        }
    }

    //ostanek
    if (lowerEdge < firstQuarter) {
        out.push_back(0);
        out.push_back(1);

        for (counterE3; counterE3 >0; counterE3--) {
            out.push_back(1);
        }
    }
    else {
        out.push_back(1);
        out.push_back(0);

        for (counterE3; counterE3 >0; counterE3--) {
            out.push_back(0);
        }
    }

    return out;
}

std::vector<char> ArithmeticCoding::Decode() {    
    unsigned int lowerEdge = 0;
    unsigned int upperEdge = pow(2,globalIntervalBit-1)-1;
    unsigned int seccondQuarter = std::floor(static_cast<double>((upperEdge +1)) / 2);
    unsigned int firstQuarter = std::floor(seccondQuarter/2);
    unsigned int thirdQuarter = std::floor(firstQuarter * 3);

    std::vector<char> out;

    std::vector<bool> array;
    for (unsigned int x = 0; x < globalIntervalBit-1; x++) {
        array.push_back(binaryData[x]);
    }

    for (auto element = binaryData.begin(); element != binaryData.end();) {
        unsigned int step = calcStep(lowerEdge, upperEdge, data.size());
        out.push_back(frequencyTable->getCharacter(static_cast<float>((fromVector(array) - lowerEdge)) / step));
        upperEdge = lowerEdge + step * frequencyTable->upperEdge(*element) -1;
        lowerEdge = lowerEdge + step * frequencyTable->lowerEdge(*element);
    

        while (upperEdge < seccondQuarter || lowerEdge >= seccondQuarter) {
            
            if (upperEdge < seccondQuarter) {
                //E1
                lowerEdge*=2;
                upperEdge=(upperEdge*2)+1;

            }
            if (lowerEdge >= seccondQuarter) {
                lowerEdge = 2*(lowerEdge - seccondQuarter);
                upperEdge = 2*(upperEdge - seccondQuarter) + 1;
            }
        }


        while (lowerEdge >= firstQuarter && upperEdge < thirdQuarter) {
            lowerEdge = 2*(lowerEdge - firstQuarter);
            upperEdge = 2*(upperEdge - firstQuarter) + 1;
        }
    }

    return out;
}