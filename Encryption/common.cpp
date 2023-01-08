#include "common.h"
#include <fstream>
#include <iostream>


int getFileSize(const char* fileName)
{
	std::fstream fin;
	fin.open(fileName, std::ios_base::in);
	if (!fin.is_open())
		std::cerr << "Could not open " << fileName << std::endl;
	fin.seekg(0, std::ios_base::end);
	int fileSize = fin.tellg();
	return fileSize;
}
