#pragma once

#include <algorithm>
#include <sstream>
#include <string.h>
#include <map>
#include <vector>

#include "Node.h"

class FrequencyTable
{
private:
    std::vector<Node*> nodes;

public:
    FrequencyTable(std::vector<unsigned char> data);
    FrequencyTable(std::vector<Node*> nodes);
    ~FrequencyTable();

    float frequency(unsigned char c);
    unsigned int lowerEdge(unsigned char c);
    unsigned int upperEdge(unsigned char c);
    std::vector<Node*> getNodes();

    unsigned char getCharacter(float value);

    static std::map<unsigned char, unsigned int> commonDictionary();

    std::string toString();
};

FrequencyTable::FrequencyTable(std::vector<unsigned char> data)
{
    std::map<unsigned char, unsigned int> mp = FrequencyTable::commonDictionary();

    for (auto element : data) {
        mp[element]++;
    }

    unsigned int lowerEdge = 0;
    unsigned int upperEdge = 0;
    for (auto element : mp) {
        if (element.second != 0) {
            upperEdge += element.second;
            nodes.push_back(new Node(element.first, element.second, (float)element.second/data.size(), lowerEdge, upperEdge));
            lowerEdge = upperEdge;
        }
    }
}

FrequencyTable::FrequencyTable(std::vector<Node*> nodes) : nodes(nodes) {}

FrequencyTable::~FrequencyTable()
{
}

float FrequencyTable::frequency(unsigned char c) {
    for (auto element : nodes) {
        if (element->getSymbol() == c) {
            return element->getFrequency();
        }
    }

    throw "Character not found";
}


unsigned int FrequencyTable::lowerEdge(unsigned char c) {
    for (auto element : nodes) {
        if (element->getSymbol() == c) {
            return element->getLowerEdge();
        }
    }

    throw "Character not found";
}


unsigned int FrequencyTable::upperEdge(unsigned char c) {
    for (auto element : nodes) {
        if (element->getSymbol() == c) {
            return element->getUpperEdge();
        }
    }

    throw "Character not found";
}


std::vector<Node*> FrequencyTable::getNodes() {
    return nodes;
}

unsigned char FrequencyTable::getCharacter(float value) {
    for (auto element : nodes) {
        if (element->getLowerEdge() < value && value < element->getUpperEdge()) {
            return element->getSymbol();
        }
    }

    throw "Character not found";
}

std::map<unsigned char, unsigned int> FrequencyTable::commonDictionary() {
    std::map<unsigned char, unsigned int> mp;

    for (unsigned int x = 0; x < 256; x++) {
        mp.insert(std::pair<unsigned char, unsigned int>(static_cast<char>(x), 0));
    }

    return mp;
}


std::string FrequencyTable::toString() {
    std::stringstream ss;

    for (auto element : nodes) {
        if (element->getFrequency() != 0) {
            ss << element->toString() << std::endl;
        }

    }

    return ss.str();
}