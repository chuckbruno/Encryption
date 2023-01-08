// Encryption.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <fstream>
#include <string>
//#include "Encryption.h"
#include "EncryptorEngine.h"
#include "common.h"

//args:
//1: mel path
//2: melx path
//3: token


int main(int args, char* argv[])
{
	if (args != 4)
	{
		std::cerr << "Syntax error, check parameters";
		return -1;
	}
	std::fstream finout;
	const char* fileName = argv[1];
	//const char* fileName = "E:/VisualStudioProj/Encryption/Encryption/createCube.mel";
	finout.open(fileName, std::ios_base::in|std::ios_base::binary);
	if (!finout.is_open())
		std::cerr << "Could not open " << fileName << std::endl;

	//char buffer[1024];
	int fileSize = getFileSize(fileName);

	char* buffer = new char[fileSize + 1];

	//fin.seekg(0, std::ios_base::end);
	//auto fileSize = fin.tellg();

	//std::cout << fileSize << std::endl;
	//fin.seekg(0, std::ios_base::beg);

	finout.read(buffer, fileSize);
	finout.close();

	buffer[fileSize] = '\0';

	uLong bound = compressBound(fileSize);
	Bytef* data = new Bytef[bound];
	uLongf outLen;
	encrypt(argv[3], buffer, fileSize, &outLen, data);
	//encrypt("test", buffer, fileSize, &outLen, data);

	std::cout << data << std::endl;

	//decrypt(buffer, fileSize);
	//std::cout << buffer << std::endl;

	const char* outFileName = argv[2];
	finout.open(outFileName, std::ios_base::out | std::ios_base::binary);
	if (!finout.is_open())
		std::cerr << "Could not open " << outFileName << std::endl;
	finout.write((const char*)(&fileSize), sizeof(fileSize));
	finout.write((const char*)data, outLen);

	delete[] buffer;
	delete[] data;

	return 0;
}
