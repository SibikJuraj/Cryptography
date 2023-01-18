#pragma once
#include "Cipher.h"

struct AffineKey
{
    int k1;
    int k2;
};

class Affine : public Cipher<AffineKey, std::string>
{
public:
	Affine();
	virtual std::string encrypt(const std::string& input) override;
	virtual std::string decrypt(const std::string& input) override;
    virtual std::string update(const std::string& input) override;
    virtual bool tryFindKey(const std::string& input) override
    { 
        return false; 
    }
    virtual const char* getName() override;
};

inline Affine::Affine()
    : Cipher(AffineKey())
{
}

inline std::string Affine::update(const std::string& input)
{
    return m_CipherMode == MODE_DECRYPT ? decrypt(input) : encrypt(input);
}

inline std::string Affine::encrypt(const std::string& input)
{
    throw std::logic_error("Not implemented");
}

inline std::string Affine::decrypt(const std::string& input)
{
    m_CipherMode = MODE_DECRYPT;
    std::string_view rawText{ input };

    std::string output{};
    for (int i{ 0 }; i < rawText.size(); ++i)
    {
        auto letter{ rawText[i] };
        letter -= 'A';
        int alphabetLength{ 26 };
        if (alphabetLength == 26)
            if (m_CipherKey.k1 % 2 == 1 && m_CipherKey.k1 != 13)
                letter = (m_CipherKey.k1 * (letter - m_CipherKey.k2)) % alphabetLength;

        if (letter < 0)
            letter += alphabetLength;
        output += letter + 'A';
    }
    return output;
}

inline const char* Affine::getName()
{
    return "Affine";
}

