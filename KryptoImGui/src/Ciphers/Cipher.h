#pragma once
#include <vector>

class Cipher
{
public:
	virtual const char* encrypt(const char* text) = 0;
	virtual const char* decrypt(const char* text) = 0;
};