#pragma once
#include "Cipher.h"
#include "Engine/Text.h"
#include <string_view>

class Affine : public Cipher
{
public:
	Affine(CryptingMode mode);
	virtual void encrypt(Text& output, bool fineTuning) override;
	virtual void decrypt(Text& output, bool fineTuning) override;
	virtual char cryptingFormula(char letter) override;
};