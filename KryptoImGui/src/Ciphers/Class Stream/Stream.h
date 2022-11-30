#pragma once
#include <Ciphers/Abstract Class Cipher/Cipher.h>

class Stream : public Cipher
{
public:
	Stream();
	virtual Text encrypt(const Text& input, bool fineTuning) override;
	virtual Text decrypt(const Text& input, bool fineTuning) override;
	virtual char encryptingFormula(char letter) override;
	virtual char decryptingFormula(char letter) override;
};