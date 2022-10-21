#include "Cipher.h"

Cipher::Cipher(std::vector<int> keys)
	:  m_Keys{keys}, m_Mode{CryptingMode::decrypt}
{
}

Text Cipher::execute(const Text& input, const CryptingMode& mode, bool fineTuning)
{
	if (mode == CryptingMode::encrypt)
	{
		m_Mode = CryptingMode::encrypt;
		return encrypt(input, fineTuning);
	}
	else
	{
		m_Mode = CryptingMode::decrypt;
		return decrypt(input, fineTuning);
	}
}

void Cipher::setKey(int index, int value)
{
	if (index >= 0 && index < m_Keys.size())
		m_Keys[index] = value;
}

int Cipher::getKey(int index)
{
	if (index >= 0 && index < m_Keys.size())
		return m_Keys[index];
	return -1;
}

CryptingMode Cipher::getMode()
{
	return m_Mode;
}

std::vector<int>& Cipher::getKeys()
{
	return m_Keys;
}
