#pragma once
#include "Cipher.h"
#include "Engine/Text.h"
#include <string_view>

class Caesar : public Cipher
{
public:
	Caesar(CryptingMode mode);
	virtual Text encrypt(const Text& input, bool fineTuning) override;
	virtual Text decrypt(const Text& input, bool fineTuning) override;
	virtual char cryptingFormula(char letter) override;
};