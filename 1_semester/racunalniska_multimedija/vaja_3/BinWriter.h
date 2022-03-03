#pragma once
#include <fstream>
#include <string>
#include <bitset>

class BinWriter
{
private:
	std::ofstream input;
	char byte = 0;	//shranimo 1 byte
	int counter = 0;	//stevec bitov

public:
	BinWriter(std::string path) {
		input.open(path, std::ios::binary);
	}

	~BinWriter() {
		if (counter > 0) {
			//byte = 0;
			input.write(&byte, 1);
		}
		input.close();
	}

	char getByte() {
		return byte;
	}

	int getCounter() {
		return counter;
	}

	void writeBit(bool b) {
		if (counter == 8) {
			input.write(&byte, 1);
			counter = 0;
			byte = 0;
		}
		byte ^= (-b ^ byte) & (1 << counter);
		counter++;
	}

	void writeByte(unsigned char c) {
		std::bitset<8> bits(c);
		for (short x = 7; x >= 0; x--) {
			writeBit(bits[x]);
		}
		//input.write((char*)&c, 1);
	}

	void writeInt(int i) {
		std::bitset<32> bits(i);
		for (short x = 31; x >= 0; x--) {
			writeBit(bits[x]);
		}
		//input.write((char*)&i, 4);
	}

	void writeFloat(float f) {
		std::bitset<32> bits(f);
		for (short x = 31; x >= 0; x--) {
			writeBit(bits[x]);
		}
		//input.write((char*)&f, 4);
	}

	void writeShort(short s) {
		std::bitset<16> bits(s);
		for (short x = 15; x >= 0; x--) {
			writeBit(bits[x]);
		}
		//input.write((char*)&s, 2);
	}
};

