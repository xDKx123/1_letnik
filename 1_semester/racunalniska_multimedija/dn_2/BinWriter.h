#pragma once
#include <fstream>
#include <string>

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

	void writeByte(char c) {
		input.write((char*)&c, 1);
	}

	void writeInt(int i) {
		input.write((char*)&i, 4);
	}

	void writeFloat(float f) {
		input.write((char*)&f, 4);
	}

	void writeShort(short s) {
		input.write((char*)&s, 2);
	}
};

