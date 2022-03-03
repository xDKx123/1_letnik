#include "BinReader.h"

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

char BinReader::readByte() {
	input.read((char*)&byte, 1);
	return byte;
}

bool BinReader::isEof()
{
	return input.eof();
}