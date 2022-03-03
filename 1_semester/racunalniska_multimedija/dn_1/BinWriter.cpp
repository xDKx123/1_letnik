#include "BinWriter.h"

BinWriter::BinWriter(std::string path)
{
	input.open(path, std::ios::binary);
}

BinWriter::~BinWriter()
{
	if (counter > 0) {
		input.write(&byte, 1);
	}
	input.close();
}

void BinWriter::writeByte(char c)
{
	input.write((char*)&c, 1);
}