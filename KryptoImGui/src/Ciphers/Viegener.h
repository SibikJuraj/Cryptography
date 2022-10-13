#pragma once
#include "Cipher.h"
#include <vector>

class Viegener : public Cipher
{
public:
	Viegener();
	~Viegener();

	virtual const char* encrypt(const char* text) override;
	virtual const char* decrypt(const char* text) override;
};