#pragma once
#include <string_view>
#include <array>
#include <utility>

#include "Cipher.h"
#include "Text/Text.h"

class Affine : public Cipher
{
public:
	Affine();
	virtual Text encrypt(const Text& input, bool fineTuning) override;
	virtual Text decrypt(const Text& input, bool fineTuning) override;
	virtual char cryptingFormula(char letter) override;
};