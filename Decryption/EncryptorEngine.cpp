#include "EncryptorEngine.h"


void encrypt(char* buffer, int size)
{
	for (int i = 0; i < size; ++i)
	{
		buffer[i] = buffer[i] + 1;
	}
}

void decrypt(char* buffer, int size)
{
	for (int i = 0; i < size; ++i)
	{
		buffer[i] = buffer[i] - 1;
	}
}