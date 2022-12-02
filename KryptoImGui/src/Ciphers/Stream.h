#pragma once
#include <Ciphers/Cipher.h>
#include "StreamGen.h"

class Stream : public CipherCore<int>
{
public:
	Stream();
	virtual std::string encrypt(const std::string_view input) override;
	virtual std::string decrypt(const std::string_view input) override;
	virtual char encryptingFormula(char letter) override;
	virtual char decryptingFormula(char letter) override;
};

inline Stream::Stream() 
	: CipherCore(std::vector<int>(2))
{
}

inline std::string Stream::encrypt(const std::string_view input)
{
	throw std::logic_error("Not implemented");
}

inline std::string Stream::decrypt(const std::string_view input)
{
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

inline char Stream::encryptingFormula(char letter)
{
	return 0;
}

inline char Stream::decryptingFormula(char letter)
{
	return 0;
}