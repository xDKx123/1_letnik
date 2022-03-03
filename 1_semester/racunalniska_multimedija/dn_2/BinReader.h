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
	BinReader(std::string path) {
		input.open(path, std::ios::binary);
		byte = 0;
		counter = 0;
	}


	~BinReader(){
		input.close();
	}

	bool isEof() {
		return input.eof();
	}

	bool readBit() {
		if (counter == 8) {
			input.read((char*)&byte, 1);
			counter = 0;
		}

		bool b = (byte >> counter) & 1;
		counter++;
		return b;
	}

	char readByte() {
		input.read((char*)&byte, 1);
		return byte;
	}

	int readInt() {
		int i;
		input.read((char*)&i, 4);
		return i;
	}

	float readFloat() {
		float f;
		input.read((char*)&f, 4);
		return f;
	}

	short readShort() {
		short s;
		input.read((char*)&s, 2);
		return s;
	}
};

