#pragma once
#include <string_view>
#include <array>
#include <utility>

#include "Cipher.h"
#include "Engine/Text.h"
class Affine : public Cipher
{
public:
	Affine(CryptingMode mode);
	virtual Text encrypt(const Text& input, bool fineTuning) override;
	virtual Text decrypt(const Text& input, bool fineTuning) override;
	virtual char cryptingFormula(char letter) override;
private:
};