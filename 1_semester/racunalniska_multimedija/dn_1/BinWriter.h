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
	BinWriter(std::string path);
	~BinWriter();

	void writeByte(char c);
};

