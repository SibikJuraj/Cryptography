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
	void execute(Text& output, const CryptingMode& mode, bool fineTuning = false);
	void setKey(int index, int value);
	int getKey(int index);
	std::vector<int>& getKeys();
protected:
	std::vector<int> m_Keys;
	CryptingMode m_Mode;

	virtual void encrypt(Text& output, bool fineTuning) = 0;
	virtual void decrypt(Text& output, bool fineTuning) = 0;
	virtual char cryptingFormula(char letter, int alphabetLength) = 0;

};