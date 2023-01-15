#pragma once
#include <vector>
#include <string>
#include <string_view>
#include <stdexcept>

#include <Config.h>
#include <Text/Text.h>
#include <Text/AnalysisOfLang.h>

class ICipher
{
public:
	virtual std::string encrypt(const std::string_view input) = 0;
	virtual std::string decrypt(const std::string_view input) = 0;
	virtual std::string update(const std::string_view input) = 0;
	virtual const char* getName() = 0;

protected:
	virtual char encryptingFormula(char letter) = 0;
	virtual char decryptingFormula(char letter) = 0;
};

template<typename K>
class Cipher : public ICipher
{
public:
	Cipher(K key) : m_CipherKey{ key }, m_CipherMode{ MODE_DECRYPT } {}
protected:
	K m_CipherKey;
	CipherMode m_CipherMode;
};
