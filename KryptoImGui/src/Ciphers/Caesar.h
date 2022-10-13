#pragma once
#include "Cipher.h"
#include <vector>

class Caesar : public Cipher
{
public:
	Caesar();
	~Caesar();

	virtual const char* encrypt(const char* text) override;
	virtual const char* decrypt(const char* text) override;
	int m_K1;
};