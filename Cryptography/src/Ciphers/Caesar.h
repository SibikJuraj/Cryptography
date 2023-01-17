#pragma once
#include "Cipher.h"

struct CaesarKey
{
    int k1;
};

class Caesar : public Cipher<CaesarKey, std::string>
{
public:
	Caesar();
    virtual std::string encrypt(const std::string& input) override;
    virtual std::string decrypt(const std::string& input) override;
    virtual std::string update(const std::string& input) override;
    virtual bool tryFindKey(const std::string& input) override
    {
        return false;
    }
	virtual const char* getName() override;
protected:
	virtual char encryptingFormula(char letter) override;
	virtual char decryptingFormula(char letter) override;
};

inline Caesar::Caesar()
    : Cipher(CaesarKey())
{
}

inline std::string Caesar::update(const std::string& input)
{
    return m_CipherMode == MODE_DECRYPT ? decrypt(input) : encrypt(input);
}

inline std::string Caesar::encrypt(const std::string& input)
{
    throw std::logic_error("Not implemented");
}

inline std::string Caesar::decrypt(const std::string& input)
{
    m_CipherMode = MODE_DECRYPT;
    double max{ -1.0 };
    int alphabetLength{ 26 };
    AnalysisOfText analysis{ input };
    for (char i{ 'A' }; i < 'A' + alphabetLength; ++i)
    {
        if (max < analysis[i])
        {
            max = analysis[i];
            m_CipherKey.k1 = i;
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
    letter = (letter - m_CipherKey.k1) % alphabetLength;

    if (letter < 0)
        letter += alphabetLength;
    return letter + 'A';
}

inline const char* Caesar::getName()
{
    return "Caesar";
}

