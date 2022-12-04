#pragma once

#include <Ciphers/Cipher.h>
#include <armadillo>

class Hill : public CipherCore<int>
{
public:
    Hill(std::vector<int> code);
    virtual std::string encrypt(const std::string_view input) override;
    virtual std::string decrypt(const std::string_view input) override;
    virtual char encryptingFormula(char letter) override;
    virtual char decryptingFormula(char letter) override;
};

inline Hill::Hill(std::vector<int> code)
    : CipherCore(code)
{
}

inline std::string Hill::encrypt(const std::string_view input)
{
    throw std::logic_error("Not implemented");
}

inline std::string Hill::decrypt(const std::string_view input)
{
    arma::Mat<int> matA{ {3, 7, 20}, {17, 24, 17}, {0, 9, 0 } };
    arma::Mat<int> matB(matA.n_rows, matA.n_cols);
    int k{ 0 };
    for (int i{ 0 }; i < matB.n_cols; ++i)
    {
        for (int j{ 0 }; j < matB.n_rows; ++j)
        {
            matB(j, i) = Text::toInt(input[k]);
            ++k;
        }
    }

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
