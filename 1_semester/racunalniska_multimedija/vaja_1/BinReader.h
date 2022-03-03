#pragma once

#include <fstream>
#include <string>

class BinReader
{
private:
	std::ifstream input;
	char byte;
	int counter;

public:
	BinReader(std::string path);
	~BinReader();

	bool isEof();

	bool readBit();
	char readByte();
	int readInt();
	float readFloat();
	short readShort();
};

BinReader::BinReader(std::string path)
{
	input.open(path, std::ios::binary);
	byte = 0;
	counter = 0;
}

BinReader::~BinReader()
{
	input.close();
}

bool BinReader::readBit() {
	if (counter == 8) {
		input.read((char*)&byte, 1);
		counter = 0;
	}

	bool b = (byte >> counter) & 1;
	counter++;
	return b;
}

char BinReader::readByte() {
	char c;
	input.read((char*)&c, 1);
	return c;
}

bool BinReader::isEof()
{
	return input.eof();
}

int BinReader::readInt() {
	int i;
	input.read((char*)&i, 4);
	return i;
}

float BinReader::readFloat() {
	float f;
	input.read((char*)&f, 4);
	return f;
}

short BinReader::readShort() {
	short s;
	input.read((char*)&s, 2);
	return s;
}