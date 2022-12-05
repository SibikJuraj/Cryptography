#pragma once
#include <Ciphers/Cipher.h>
#include "StreamGen.h"

class RSA : public CipherCore<int>
{
public:
	RSA();
	virtual std::string encrypt(const std::string_view input) override;
	virtual std::string decrypt(const std::string_view input) override;
	virtual char encryptingFormula(char letter) override;
	virtual char decryptingFormula(char letter) override;
};

inline RSA::RSA()
	: CipherCore(std::vector<int>(2))
{
}

inline std::string RSA::encrypt(const std::string_view input)
{
	throw std::logic_error("Not implemented");
}

inline std::string RSA::decrypt(const std::string_view input)
{
	n = 2164267772327;
	e = 65537;
	y = 1325266873785;

	std::string output{ };
	output.resize(input.size());

	for (int i{ 100'000 }; i <= 999'999; ++i)
	{
		StreamGen::decrypt(std::to_string(i) + '\0', input, output);
		auto letterCount{ Text::letterCount(output) };

		if (letterCount > output.length() * 0.65)
		{
			output.erase(std::remove(output.begin(), output.end(), '\r'), output.end());

			output += "\nPassword : " + std::to_string(i);
			break;
		}
	}
	return output;
}

inline char RSA::encryptingFormula(char letter)
{
	return 0;
}

inline char RSA::decryptingFormula(char letter)
{
	return 0;
}