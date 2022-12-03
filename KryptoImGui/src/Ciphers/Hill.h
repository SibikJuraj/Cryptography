#pragma once
#include <Eigen/Dense>

#include <Ciphers/Cipher.h>

class Hill : public CipherCore<int>
{
public:
    Hill(int size);
    virtual std::string encrypt(const std::string_view input) override;
    virtual std::string decrypt(const std::string_view input) override;
    virtual char encryptingFormula(char letter) override;
    virtual char decryptingFormula(char letter) override;
private:
    int m_Dimension;
};

inline Hill::Hill(int size)
    : CipherCore(std::vector<int>{size * size}), m_Dimension{ size }
{
}

inline std::string Hill::encrypt(const std::string_view input)
{
    throw std::logic_error("Not implemented");
}

inline std::string Hill::decrypt(const std::string_view input)
{
    Eigen::Matrix matrix{ m_Dimension, m_Dimension };
    matrix
    std::string output{};
    for (int i{ 0 }; i < input.size(); ++i)
        output += decryptingFormula(input[i]);
    return output;
}

inline char Hill::encryptingFormula(char letter)
{
    letter -= 'A';
    int alphabetLength{ 26 };
    letter = (letter + m_Keys[0]) % alphabetLength;

    if (letter < 0)
        letter += alphabetLength;
    return letter + 'A';
}

inline char Hill::decryptingFormula(char letter)
{
    letter -= 'A';
    int alphabetLength{ 26 };
    letter = (letter - m_Keys[0]) % alphabetLength;

    if (letter < 0)
        letter += alphabetLength;
    return letter + 'A';
}
