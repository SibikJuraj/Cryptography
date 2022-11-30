#pragma once
#include <vector>
#include <string>
#include <string_view>
#include <Text/Class Text/Text.h>

class Cipher
{
public:
	Cipher(std::vector<int> keys);

	virtual Text encrypt(const Text& input, bool fineTuning) = 0;
	virtual Text decrypt(const Text& input, bool fineTuning) = 0;

	void setKey(int index, int value);
	int getKey(int index);
	std::vector<int>& getKeys();
protected:
	std::vector<int> m_Keys;
	
	virtual char encryptingFormula(char letter) = 0;
	virtual char decryptingFormula(char letter) = 0;
};