#pragma once
#include <Ciphers/Cipher.h>

class Affine : public Cipher<int>
{
public:
	Affine();
	virtual std::string encrypt(const std::string_view input) override;
	virtual std::string decrypt(const std::string_view input) override;
    virtual std::string update(const std::string_view input) override;
    virtual const char* getName() override;
protected:
	virtual char encryptingFormula(char letter) override;
	virtual char decryptingFormula(char letter) override;
};

Affine::Affine()
    : Cipher(std::vector<int>(2))
{
}

inline std::string Affine::update(const std::string_view input)
{
    std::string output{};
    for (int i{ 0 }; i < input.size(); ++i)
    {
        if (m_CipherMode == MODE_DECRYPT)
            output += decryptingFormula(input[i]);
        else
            output += encryptingFormula(input[i]);
    }
    return output;
}

inline std::string Affine::encrypt(const std::string_view input)
{
    throw std::logic_error("Not implemented");
}

inline std::string Affine::decrypt(const std::string_view input)
{
    m_CipherMode = MODE_DECRYPT;
    std::string_view rawText{ input };

    std::string output{};
    for (int i{ 0 }; i < rawText.size(); ++i)
        output += decryptingFormula(rawText[i]);
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

inline const char* Affine::getName()
{
    return "Affine";
}