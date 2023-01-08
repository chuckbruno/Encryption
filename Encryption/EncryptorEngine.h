#ifndef _ENCRYPTOR_ENGINE_
#define _ENCRYPTOR_ENGINE_

#include <zlib.h>

enum EncryptStatus
{
	kSuccess,
	kFailure
};

extern EncryptStatus encrypt(const char* buffer, int size, uLongf* outLen, Bytef* (&data));
extern EncryptStatus decrypt(const char* buffer, int size, uLongf outLen, Bytef* (&data));

#endif // !_ENCRYPTOR_ENGINE_
