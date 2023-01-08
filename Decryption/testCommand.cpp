#include "testCommand.h"
#include <maya/MString.h>
#include <maya/MArgList.h>
#include <maya/MStatus.h>
#include <maya/MGlobal.h>
#include <fstream>

#include <common.h>
#include <EncryptorEngine.h>


Decryptor::Decryptor()
{
	//empty
}

void* Decryptor::creator()
{
	return new Decryptor;
}


MStatus Decryptor::doIt(const MArgList& args)
{

	MStatus status;
	MString filePath;
	CHECK_MSTATUS_AND_RETURN_IT(args.get(0, filePath));
	std::fstream fin;
	fin.open(filePath.asChar(), std::ios_base::in | std::ios_base::binary);
	if (!fin.is_open()) 
	{
		MGlobal::displayError("Could open file: " + filePath);
		return MS::kFailure;
	
	}

	int fileSize = getFileSize(filePath.asChar());
	char* buffer = new char[fileSize + 1];
	fin.read(buffer, fileSize);
	fin.close();

	buffer[fileSize] = '\0';
	decrypt(buffer, fileSize);

	MGlobal::executeCommand(buffer);
	delete[] buffer;

	return MS::kSuccess;

}