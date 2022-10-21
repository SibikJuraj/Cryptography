#pragma once
#include <vector>
#include <string>
#include <string_view>

#include "CryptingMode.h"
#include "Engine/Text.h"

class Cipher
{
public:
	Cipher(std::vector<int> keys, CryptingMode mode);
	Text execute(const Text& input, const CryptingMode& mode, bool fineTuning = false);
	void setKey(int index, int value);
	int getKey(int index);
	CryptingMode getMode();
	std::vector<int>& getKeys();
protected:
	std::vector<int> m_Keys;
	CryptingMode m_Mode;

	virtual Text encrypt(const Text& input, bool fineTuning) = 0;
	virtual Text decrypt(const Text& input, bool fineTuning) = 0;
	virtual char cryptingFormula(char letter) = 0;

};