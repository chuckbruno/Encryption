#include "EncryptorEngine.h"
#include <cstring>


enum ApplyMode
{
	kApplyModeEncrypt,
	kApplyModeDecrypt
};

void applyToken(char* data, int len, const char* token, ApplyMode mode)
{
	int tokenLen = strlen(token);
	for (int i = 0; i < len; ++i)
	{
		if (mode == kApplyModeEncrypt)
			data[i] += token[i % tokenLen];
		else
			data[i] -= token[i % tokenLen];
	}
}


EncryptStatus encrypt(const char* token, const char* buffer, int size, uLongf* outLen, Bytef* (&data))
{
	uLongf destLen = compressBound(size);
	Bytef* destData = new Bytef[destLen];
	int status = compress(destData, &destLen, (Bytef*)buffer, size);
	if (status != Z_OK)
		return kFailure;

	applyToken((char*)destData, destLen, token, kApplyModeEncrypt);
	data = destData;
	*outLen = destLen;

	return kSuccess;
}

EncryptStatus decrypt(const char* token, const char* buffer, int size, uLongf outLen, Bytef* (&data))
{
	applyToken((char*)buffer, size, token, kApplyModeDecrypt);
	data = new Bytef[outLen];
	int status = uncompress(data, &outLen, (const Bytef*)buffer, size);
	if (status != Z_OK)
		return kFailure;
	return kSuccess;
}