#pragma once

typedef unsigned char byte;

struct StreamKey
{
	int seed;
};

class Stream : public Cipher<StreamKey>
{
public:
	Stream();
	virtual std::string encrypt(const std::string_view input) override;
	virtual std::string decrypt(const std::string_view input) override;
	virtual std::string update(const std::string_view input) override;
	virtual const char* getName() override;
protected:
	virtual char encryptingFormula(char letter) override;
	virtual char decryptingFormula(char letter) override;
private:
	byte rc4_i, rc4_j;
	byte rc4_s[256];
	byte rc4_k[256];
	
	byte* getKey(const std::string_view passwd);
	void rc4_init(const byte* key);
	byte rc4_rand();
	void encrypt(const std::string_view passwd, const std::string_view plainText, std::string& cipherText);
	void decrypt(const std::string_view passwd, const std::string_view cipherText, std::string& plainText);
};

inline Stream::Stream() 
	: Cipher(StreamKey())
{
}

inline std::string Stream::update(const std::string_view input)
{
	std::string output{ };
	output.resize(input.size());

	decrypt(std::to_string(m_CipherKey.seed)+ '\0', input, output);
	auto letterCount{ Text::letterCount(output) };

	output.erase(std::remove(output.begin(), output.end(), '\r'), output.end());

	output += "\nPassword : " + std::to_string(m_CipherKey.seed);

	return output;
}

inline std::string Stream::encrypt(const std::string_view input)
{
	throw std::logic_error("Not implemented");
}

inline std::string Stream::decrypt(const std::string_view input)
{
	m_CipherMode = MODE_DECRYPT;

	std::string output{ };
	output.resize(input.size());

	for (int i{ 100'000 }; i <= 999'999; ++i)
	{
		decrypt(std::to_string(i) + '\0', input, output);
		auto letterCount{ Text::letterCount(output) };

		if (letterCount > output.length() * 0.65)
		{
			output.erase(std::remove(output.begin(), output.end(), '\r'), output.end());

			m_CipherKey.seed = i;
			output += "\nPassword : " + std::to_string(i);
			break;
		}
	}
	return output;
}

inline char Stream::encryptingFormula(char letter)
{
	return 0;
}

inline char Stream::decryptingFormula(char letter)
{
	return 0;
}

inline const char* Stream::getName()
{
	return "Stream";
}

inline byte* Stream::getKey(const std::string_view passwd)
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

inline void Stream::encrypt(const std::string_view passwd, const std::string_view plainText, std::string& cipherText)
{
	// nastav random seed - toto je hodnota kluca
	rc4_init(getKey(passwd));

	for (int i{ 0 }; i < plainText.size(); ++i)
	{
		byte p = (byte)plainText[i];
		byte r = rc4_rand();
		byte c = p ^ r;
		cipherText[i] = c;
	}
}

inline void Stream::decrypt(const std::string_view passwd, const std::string_view cipherText, std::string& plainText)
{
	// vzhladom na operaciu XOR je sifrovanie a desifrovanie uplne rovnake
	encrypt(passwd, cipherText, plainText);
}