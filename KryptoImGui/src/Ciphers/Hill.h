#pragma once
#include <Ciphers/Cipher.h>
#include <glm/glm.hpp>

class Hill : public CipherCore<int>
{
public:
    Hill(int size);
    virtual std::string encrypt(const std::string_view input) override;
    virtual std::string decrypt(const std::string_view input) override;
    virtual char encryptingFormula(char letter) override;
    virtual char decryptingFormula(char letter) override;
};

inline Hill::Hill(int size)
    : CipherCore(std::vector<int>{size * size})
{
}

inline std::string Hill::encrypt(const std::string_view input)
{
    throw std::logic_error("Not implemented");
}

inline std::string Hill::decrypt(const std::string_view input)
{
    std::string output{};
    for (int i{ 0 }; i < input.size(); ++i)
        output += decryptingFormula(input[i]);
    output += "\n\nPassword: ";
    for (int i{ 0 }; i < m_Keys.size(); ++i)
        output += (static_cast<char>((m_Keys[i] < 0 ? m_Keys[i] + language.getAlphabetLength() : m_Keys[i]) % language.getAlphabetLength()) + 65);
    output += " length: " + std::to_string(m_Keys.size());

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
