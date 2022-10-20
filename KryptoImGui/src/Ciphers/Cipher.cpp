#include "Cipher.h"

Cipher::Cipher(std::vector<int> keys, CryptingMode mode)
	:  m_Keys{keys}, m_Mode{mode}
{
}

void Cipher::execute(Text& output, const CryptingMode& mode, bool fineTuning)
{
	if (mode == CryptingMode::encrypt)
	{
		m_Mode = CryptingMode::encrypt;
		encrypt(output, fineTuning);
	}
	else
	{
		m_Mode = CryptingMode::decrypt;
		decrypt(output, fineTuning);
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

std::vector<int>& Cipher::getKeys()
{
	return m_Keys;
}
