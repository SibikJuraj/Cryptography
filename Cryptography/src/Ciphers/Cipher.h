#pragma once
#include <vector>
#include <string>
#include <string_view>
#include <stdexcept>

#include <Config.h>
#include <Text/Text.h>
#include <Text/AnalysisOfLang.h>

template<typename K, typename T>
class Cipher
{
public:
	Cipher(K key) : m_CipherKey{ key }, m_CipherMode{ MODE_DECRYPT } {}

	K& getKey();

	virtual T encrypt(const T& input) = 0;
	virtual T decrypt(const T& input) = 0;
	virtual T update(const T& input) = 0;
	virtual bool tryFindKey(const T& input) = 0;
	virtual const char* getName() = 0;

protected:
	K m_CipherKey;
	CipherMode m_CipherMode;
};

template<typename K, typename T>
inline K& Cipher<K, T>::getKey()
{
	return m_CipherKey;
}
