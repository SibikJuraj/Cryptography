#pragma once
#include <vector>
#include <string>
#include <string_view>
#include <stdexcept>

#include <Config.h>
#include <Text/Text.h>
#include <Text/AnalysisOfLang.h>

template<typename T = int>
class Cipher 
{
public:
	Cipher(std::vector<T> keys) : m_Keys{ keys }, m_CipherMode{ MODE_DECRYPT } {}

	virtual std::string encrypt(const std::string_view input) = 0;
	virtual std::string decrypt(const std::string_view input) = 0;
	virtual std::string update(const std::string_view input) = 0;
	virtual const char* getName() = 0;

	void setKey(int index, T value);
	int getKey(int index);
	std::vector<T>& getKeys();
protected:
	virtual char encryptingFormula(char letter) = 0;
	virtual char decryptingFormula(char letter) = 0;

	std::vector<T> m_Keys;
	CipherMode m_CipherMode;
};


template <typename T>
inline void Cipher<T>::setKey(int index, T value)
{
	if (index >= 0 && index < m_Keys.size())
		m_Keys[index] = value;
}

template <typename T>
inline int Cipher<T>::getKey(int index)
{
	if (index >= 0 && index < m_Keys.size())
		return m_Keys[index];
	return -1;
}

template <typename T>
inline std::vector<T>& Cipher<T>::getKeys()
{
	return m_Keys;
}