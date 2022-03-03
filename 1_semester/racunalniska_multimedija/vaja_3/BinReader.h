#pragma once
#include <fstream>
#include <string>
#include <bitset>

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
		std::bitset<8> ch;
		
		for (short x = 7; x >= 0; x--) {
			ch[x] = readBit();
		}

		//input.read((char*)&byte, 1);
		return (unsigned char)ch.to_ulong();
	}

	int readInt() {
		// int i;
		// input.read((char*)&i, 4);
		// return i;

		std::bitset<32> ch;
		
		for (short x = 31; x >= 0; x--) {
			ch[x] = readBit();
		}

		return (int)ch.to_ulong();
	}

	float readFloat() {
		// float f;
		// input.read((char*)&f, 4);
		// return f;
		std::bitset<32> ch;
		
		for (short x = 31; x >= 0; x--) {
			ch[x] = readBit();
		}

		return (float)ch.to_ulong();
	}

	short readShort() {
		// short s;
		// input.read((char*)&s, 2);
		// return s;

		std::bitset<16> ch;
		
		for (short x = 15; x >= 0; x--) {
			ch[x] = readBit();
		}

		return (short)ch.to_ulong();
	}
};

