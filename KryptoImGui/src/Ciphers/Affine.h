#pragma once
#include "Cipher.h"

class Affine : public Cipher
{
public:
	Affine();
	virtual Text encrypt(const Text& input, bool fineTuning) override;
	virtual Text decrypt(const Text& input, bool fineTuning) override;
	virtual char encryptingFormula(char letter) override;
	virtual char decryptingFormula(char letter) override;
};