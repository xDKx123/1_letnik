#pragma once

#include <map>
#include <tuple>

#include "BinReader.h"
#include "BinWriter.h"

class Utility
{
private:
    /* data */
public:
    Utility(/* args */);
    ~Utility();

    static void writeD(std::string fileName, FrequencyTable *frequencyTable, std::vector<bool>data, short bitSize);
    static std::tuple<FrequencyTable*, std::vector<bool>, unsigned short> readD(std::string fileName);
};

Utility::Utility(/* args */)
{
}

Utility::~Utility()
{
}

void Utility::writeD(std::string fileName, FrequencyTable *frequencyTable, std::vector<bool> data, short bitSize) {
    BinWriter *bw = new BinWriter(fileName);

    bw->writeShort((unsigned short)bitSize);
    bw->writeShort((unsigned short)frequencyTable->getNodes().size());

    for (auto element : frequencyTable->getNodes()) {
        bw->writeByte(element->getSymbol());
        bw->writeInt(element->getFrequency());
    }

    for (auto b : data) {
        bw->writeBit(b);
    }

    for (int x = 0; x < 7; x++) {
        bw->writeBit(0);
    }
    bw->writeBit(1);

    delete bw;
}

std::tuple<FrequencyTable*, std::vector<bool>, unsigned short> Utility::readD(std::string fileName) {
    BinReader *br = new BinReader(fileName);

    unsigned short bitSize = br->readShort();
    unsigned short elements = br->readShort();


    std::vector<Node*> nodes;
    std::map<unsigned char, unsigned int> mp;

    unsigned long lowerEdge = 0;
    unsigned long upperEdge = 0;

    for (unsigned int x = 0; x < elements; x++) {
        char c = br->readByte();
        unsigned int i = br->readInt();
        upperEdge += i;
        nodes.push_back(new Node(c, i, 0, lowerEdge, upperEdge));
        lowerEdge = upperEdge;
    }

    FrequencyTable* frequencyTable = new FrequencyTable(nodes);

    std::vector<bool> data;

    while (!br->isEof()) {
        bool b = br->readBit();

        data.push_back(b);
    }

    for (int x = 0; x < 8; x++) {
        data.erase(data.begin());
    }

    while (data[data.size() - 1] == 0) {
        data.pop_back();
    }

    for (int x = 0; x < 8; x++) {
        data.pop_back();
    }

    delete br;

    return {frequencyTable, data, bitSize};
}