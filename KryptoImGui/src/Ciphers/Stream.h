#pragma once
#include "Cipher.h"
#include "Text/Text.h"
#include <string_view>

class Stream : public Cipher
{
public:
	Stream();
	virtual Text encrypt(const Text& input, bool fineTuning) override;
	virtual Text decrypt(const Text& input, bool fineTuning) override;
	virtual char cryptingFormula(char letter) override;
};