#pragma once

#include <sstream>
#include <string.h>

class Node
{
private:

    char symbol;
    unsigned int frequency;
    float probability;
    unsigned int lowerEdge;
    unsigned int upperEdge;

public:
    Node(char symbol, unsigned int frequency, double probability, unsigned int lowerEdge, unsigned int upperEdge);
    ~Node();

    char getSymbol();
    unsigned int getFrequency();
    float getProbability();
    unsigned int getLowerEdge();
    unsigned int getUpperEdge();

    std::string toString();
};

Node::Node(char symbol, unsigned int frequency, double probability, unsigned int lowerEdge, unsigned int upperEdge) : symbol(symbol), frequency(frequency), probability(probability), lowerEdge(lowerEdge), upperEdge(upperEdge)
{
}

Node::~Node()
{
}

char Node::getSymbol() {
    return symbol;
}

unsigned int Node::getFrequency() {
    return frequency;
}

float Node::getProbability() {
    return probability;
}

unsigned int Node::getLowerEdge() {
    return lowerEdge;
}

unsigned int Node::getUpperEdge() {
    return upperEdge;
}

std::string Node::toString() {
    std::stringstream ss;

    ss << "{\n\t" << symbol << "\n\t" << frequency << "\n\t" << probability << "\n\t" << lowerEdge << "\n\t" << upperEdge << "\n}" << std::endl;

    return ss.str();
}