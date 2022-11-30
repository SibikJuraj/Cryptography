#pragma once
#include <Ciphers/Abstract Class Cipher/Cipher.h>

class Viegener : public Cipher
{
public:
	Viegener();
	virtual Text encrypt(const Text& input, bool fineTuning) override;
	virtual Text decrypt(const Text& input, bool fineTuning) override;
	virtual char encryptingFormula(char letter) override;
	virtual char decryptingFormula(char letter) override;
private:
	int m_Counter;
};