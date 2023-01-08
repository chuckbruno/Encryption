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
	MString token;
	CHECK_MSTATUS_AND_RETURN_IT(args.get(0, filePath));
	CHECK_MSTATUS_AND_RETURN_IT(args.get(1, token));

	std::fstream fin;
	fin.open(filePath.asChar(), std::ios_base::in | std::ios_base::binary);
	if (!fin.is_open()) 
	{
		MGlobal::displayError("Could open file: " + filePath);
		return MS::kFailure;
	
	}

	int len_mel;
	fin.read((char*)(&len_mel), sizeof(len_mel));

	int len_data = getFileSize(filePath.asChar());
	len_data = len_data - sizeof(len_mel);
	char* buffer = new char[len_data];
	fin.read(buffer, len_data);
	fin.close();

	Bytef* mel = new Bytef[len_mel];
	EncryptStatus re = decrypt(token.asChar(), buffer, len_data, len_mel, mel);
	if (re != kSuccess)
	{
		MGlobal::displayError("Token was wrong");
		delete[] mel;
		delete[] buffer;
		return MStatus::kFailure;
	}

	Bytef* mel_with_end = new Bytef[len_mel + 1];
	memcpy(mel_with_end, mel, len_mel);
	mel_with_end[len_mel] = '\0';

	MGlobal::executeCommand((char *)mel_with_end);
	delete[] buffer;

	delete[] mel;
	delete[] mel_with_end;

	return MS::kSuccess;

}