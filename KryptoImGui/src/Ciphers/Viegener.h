#pragma once
#include "Cipher.h"
#include <string_view>

class Viegener : public Cipher
{
public:
	Viegener();
	virtual Text encrypt(const Text& input, bool fineTuning) override;
	virtual Text decrypt(const Text& input, bool fineTuning) override;
	virtual char cryptingFormula(char letter) override;
private:
	int m_Counter;
};