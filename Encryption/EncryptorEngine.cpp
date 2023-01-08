#include "EncryptorEngine.h"


EncryptStatus encrypt(const char* buffer, int size, uLongf* outLen, Bytef* (&data))
{
	uLongf destLen = compressBound(size);
	Bytef* destData = new Bytef[destLen];
	int status = compress(destData, &destLen, (Bytef*)buffer, size);
	if (status != Z_OK)
		return kFailure;

	data = destData;
	*outLen = destLen;

	return kSuccess;
}

EncryptStatus decrypt(const char* buffer, int size, uLongf outLen, Bytef* (&data))
{
	data = new Bytef[outLen];
	int status = uncompress(data, &outLen, (const Bytef*)buffer, size);
	if (status != Z_OK)
		return kFailure;
	return kSuccess;
}