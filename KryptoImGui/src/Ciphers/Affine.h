#pragma once
#include "Cipher.h"
#include <vector>

class Affine : public Cipher
{
public:
	Affine();
	~Affine();

	virtual const char* encrypt(const char* text) override;
	virtual const char* decrypt(const char* text) override;
};