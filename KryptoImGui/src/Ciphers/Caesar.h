#pragma once
#include <Ciphers/Cipher.h>

class Caesar : public CipherCore<int>
{
public:
	Caesar();
    virtual std::string encrypt(const std::string_view input) override;
    virtual std::string decrypt(const std::string_view input) override;
	virtual char encryptingFormula(char letter) override;
	virtual char decryptingFormula(char letter) override;
};

inline Caesar::Caesar()
    : CipherCore(std::vector<int>(1))
{
}

inline std::string Caesar::encrypt(const std::string_view input)
{
    throw std::logic_error("Not implemented");
}

inline std::string Caesar::decrypt(const std::string_view input)
{
    double max{ -1.0 };
    int alphabetLength{ 26 };
    AnalysisOfText analysis{ input };
    for (char i{ 'A' }; i < 'A' + alphabetLength; ++i)
    {
        if (max < analysis[i])
        {
            max = analysis[i];
            m_Keys[0] = i;
        }
    }

    std::string output{};
    for (int i{ 0 }; i < input.size(); ++i)
        output += decryptingFormula(input[i]);

    return output;
}

inline char Caesar::encryptingFormula(char letter)
{
    throw std::logic_error("Not implemented");
}

inline char Caesar::decryptingFormula(char letter)
{
    letter -= 'A';
    int alphabetLength{ 26 };
    letter = (letter - m_Keys[0]) % alphabetLength;

    if (letter < 0)
        letter += alphabetLength;
    return letter + 'A';
}
