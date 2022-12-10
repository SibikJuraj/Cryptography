#pragma once
#include <vector>
#include <string>
#include <string_view>
#include <stdexcept>

#include <Config.h>
#include <Text/Text.h>
#include <Text/AnalysisOfLang.h>

class Cipher {
public:
	Cipher() = default;

	virtual std::string encrypt(const std::string_view input) = 0;
	virtual std::string decrypt(const std::string_view input) = 0;

	virtual char encryptingFormula(char letter) = 0;
	virtual char decryptingFormula(char letter) = 0;
	virtual const char* getName() = 0;
};

template<typename T>
class CipherCore : public Cipher
{
public:
	CipherCore(std::vector<T> keys);

	void setKey(int index, T value);
	int getKey(int index);
	std::vector<T>& getKeys();
protected:
	std::vector<T> m_Keys;
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