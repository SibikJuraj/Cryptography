#pragma once
#include "Cipher.h"

typedef unsigned char byte;

struct StreamKey
{
	int seed;
};

class Stream : public Cipher<StreamKey, std::string>
{
public:
	Stream();
	virtual std::string encrypt(const std::string& input) override;
	virtual std::string decrypt(const std::string& input) override;
	virtual std::string update(const std::string& input) override;
	virtual bool tryFindKey(const std::string& input) override;
	virtual const char* getName() override;
private:
	byte rc4_i, rc4_j;
	byte rc4_s[256];
	byte rc4_k[256];
	
	byte* initKey(const std::string& passwd);
	void rc4_init(const byte* key);
	byte rc4_rand();
};

inline Stream::Stream() 
	: Cipher(StreamKey())
{
}

inline std::string Stream::update(const std::string& input)
{
	return m_CipherMode == MODE_DECRYPT ? decrypt(input) : encrypt(input);
}

inline std::string Stream::encrypt(const std::string& input)
{
	throw std::logic_error("Not implemented");
}

inline std::string Stream::decrypt(const std::string& input)
{
	m_CipherMode = MODE_DECRYPT;

	std::string output{ };
	output.resize(input.size());

	rc4_init(initKey(std::to_string(m_CipherKey.seed)));

	for (int i{ 0 }; i < input.size(); ++i)
	{
		byte p = (byte)input[i];
		byte r = rc4_rand();
		byte c = p ^ r;
		output[i] = c;
	}

	return output;
}

inline const char* Stream::getName()
{
	return "Stream";
}

inline byte* Stream::initKey(const std::string& passwd)
{
	for (int i{ 0 }, j = { 0 }; i < 256; ++i)
	{
		rc4_k[i] = (byte)passwd[j];
		if (passwd[j] != 0)
			++j;
		else
			j = 0;
	}

	return rc4_k;
}

inline void Stream::rc4_init(const byte* key)
{
	for (int i = 0; i < 256; i++)
	{
		rc4_s[i] = i;
	}

	for (int i = 0, j = 0; i < 256; i++)
	{
		j = (j + rc4_s[i] + key[i]) % 256;
		// swap(rc4_s[i], rc4_s[j])
		byte tmp = rc4_s[i]; rc4_s[i] = rc4_s[j]; rc4_s[j] = tmp;
	}

	rc4_i = 0;
	rc4_j = 0;
}

inline byte Stream::rc4_rand()
{
	rc4_i = (rc4_i + 1) % 256; // kedze rc4_i je typu byte, stacilo by aj rc4_i++;
	rc4_j = (rc4_j + rc4_s[rc4_i]) % 256; // aj tu je modulo 256 nepotrebne
	// swap(rc4_s[rc4_i], rc4_s[rc4_j])
	byte tmp = rc4_s[rc4_i]; rc4_s[rc4_i] = rc4_s[rc4_j]; rc4_s[rc4_j] = tmp;

	byte t = (rc4_s[rc4_i] + rc4_s[rc4_j]) % 256;
	return rc4_s[t];
}

inline bool Stream::tryFindKey(const std::string& input)
{
	for (int i{ 100'000 }; i <= 999'999; ++i)
	{
		m_CipherKey.seed = i;
		std::string output{ decrypt(input) };
		auto letterCount{ Text::letterCount(output) };

		if (letterCount > output.length() * 0.65)
		{
			output.erase(std::remove(output.begin(), output.end(), '\r'), output.end());

			output += "\nPassword : " + std::to_string(i);
			break;
		}
	}
	return true;
}