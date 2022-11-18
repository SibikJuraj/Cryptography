#include "Cipher.h"

Cipher::Cipher(std::vector<int> keys)
	:  m_Keys{keys}
{
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
