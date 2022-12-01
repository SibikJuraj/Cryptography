#pragma once
#include <vector>
#include <string>
#include <string_view>
#include <Text/Class Text/Text.h>

class Cipher {
public:
	Cipher() = default;
};

template<typename T>
class CipherCore : public Cipher
{
public:
	CipherCore(std::vector<T> keys);

	virtual Text encrypt(const Text& input, bool fineTuning) = 0;
	virtual Text decrypt(const Text& input, bool fineTuning) = 0;

	void setKey(int index, T value);
	int getKey(int index);
	std::vector<T>& getKeys();
protected:
	std::vector<T> m_Keys;
	
	virtual char encryptingFormula(char letter) = 0;
	virtual char decryptingFormula(char letter) = 0;
};

template <typename T>
inline CipherCore<T>::CipherCore(std::vector<T> keys)
	: m_Keys{ keys }
{
}

template <typename T>
inline void CipherCore<T>::setKey(int index, T value)
{
	if (index >= 0 && index < m_Keys.size())
		m_Keys[index] = value;
}

template <typename T>
inline int CipherCore<T>::getKey(int index)
{
	if (index >= 0 && index < m_Keys.size())
		return m_Keys[index];
	return -1;
}

template <typename T>
inline std::vector<T>& CipherCore<T>::getKeys()
{
	return m_Keys;
}