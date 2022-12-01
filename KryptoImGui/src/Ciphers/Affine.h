#pragma once
#include <Ciphers/Cipher.h>

class Affine : public CipherCore<int>
{
public:
	Affine();
	virtual Text encrypt(const Text& input) override;
	virtual Text decrypt(const Text& input) override;
	virtual char encryptingFormula(char letter) override;
	virtual char decryptingFormula(char letter) override;
};

Affine::Affine()
    : CipherCore(std::vector<int>(2))
{
}

inline Text Affine::encrypt(const Text& input)
{
    throw std::logic_error("Not implemented");
}

inline Text Affine::decrypt(const Text& input)
{
    std::string_view rawText{ input.getRawText() };

    Text output;
    for (int i{ 0 }; i < rawText.size(); ++i)
        output.addLetter(decryptingFormula(rawText[i]));
    return output;
}

inline char Affine::encryptingFormula(char letter)
{
    throw std::logic_error("Not implemented");
}

inline char Affine::decryptingFormula(char letter)
{
    letter -= 'A';
    int alphabetLength{ 26 };
    if (alphabetLength == 26)
        if (m_Keys[0] % 2 == 1 && m_Keys[0] != 13)
            letter = (m_Keys[0] * (letter - m_Keys[1])) % alphabetLength;

    if (letter < 0)
        letter += alphabetLength;
    return letter + 'A';
}