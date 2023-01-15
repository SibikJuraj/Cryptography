#pragma once
#include <Ciphers/Cipher.h>
#include <matrix.h>
#include <matrix_operation.h>

struct HillKey
{
    std::vector<int> keys;

    HillKey(std::vector<int> pKeys) 
        : keys{ pKeys } {}
};

class Hill : public Cipher<HillKey>
{
public:
    Hill(HillKey key);
    Hill();
    virtual std::string encrypt(const std::string_view input) override;
    virtual std::string decrypt(const std::string_view input) override;
    virtual std::string update(const std::string_view input) override;
    virtual const char* getName() override;
protected:
    virtual char encryptingFormula(char letter) override;
    virtual char decryptingFormula(char letter) override;
};

inline Hill::Hill()
    : Hill(HillKey({ 3, 7, 20, 17, 24, 17, 0, 9, 0 }))
{
}

inline Hill::Hill(HillKey key)
    : Cipher(key)
{
}

inline std::string Hill::update(const std::string_view input)
{
    return m_CipherMode == MODE_DECRYPT ? decrypt(input) : encrypt(input);
}

inline std::string Hill::encrypt(const std::string_view input)
{
    throw std::logic_error("Not implemented");
}

inline std::string Hill::decrypt(const std::string_view input)
{
    m_CipherMode = MODE_DECRYPT;
    int dimension{ static_cast<int>(std::sqrt(m_CipherKey.keys.size())) };
    Matrix<double> matA(dimension, dimension);
    for (int i{ 0 }; i < matA.cols(); ++i)
    {
        for (int j{ 0 }; j < matA.rows(); ++j)
        {
            matA(j, i) = Text::toInt(input[(i * matA.rows()) + j]);
        }
    }
    const int moduloValue = 26;

    auto determ = static_cast<int>(det(matA)) % moduloValue;
    if (determ < 0)
        determ += moduloValue;

    int modVal{ 1 };
    while (modVal <= moduloValue)
    {
        auto val{ determ * modVal % moduloValue };
        if (val < 0)
            val += moduloValue;
        if (val == 1)
            break;
        ++modVal;
    }
    auto matB{ ((inverse(matA) * det(matA)).castWRound<int>() * modVal).modulo(moduloValue) };
    Matrix<int> matC(dimension, dimension);
    for (int i{ 0 }; i < matC.cols(); ++i)
    {
        for (int j{ 0 }; j < matC.rows(); ++j)
        {
            matC(i, j) = m_CipherKey.keys[(i * matC.rows()) + j];
        }
    }
    auto matF{ matmul(matC, matB).modulo(moduloValue)};
    std::string output{};

    int txtPos{0};
    while (txtPos < input.size())
    {
        Matrix<int> readMat(dimension, dimension, 0);
        for (int i{ 0 }; i < readMat.cols(); ++i)
        {
            for (int j{ 0 }; j < readMat.rows(); ++j)
            {
                if (txtPos < input.size())
                {
                    readMat(j, i) = Text::toInt(input[txtPos]);
                    ++txtPos;
                }
                else
                    break;
            }
        }
        readMat = matmul(matF, readMat).modulo(moduloValue);

        for (int i{ 0 }; i < readMat.cols(); ++i)
        {
            for (int j{ 0 }; j < readMat.rows(); ++j)
            {
                if (output.size() < input.size())
                    output += Text::toChar(readMat(j, i));
            }
        }
    }

    /*
    for (int i{ 0 }; i < input.size(); ++i)
        output += decryptingFormula(input[i]);
    */
    return output;
}

inline char Hill::encryptingFormula(char letter)
{
    letter -= 'A';
    int alphabetLength{ 26 };
    letter = (letter + m_CipherKey.keys[0]) % alphabetLength;

    if (letter < 0)
        letter += alphabetLength;
    return letter + 'A';
}

inline char Hill::decryptingFormula(char letter)
{
    letter -= 'A';
    int alphabetLength{ 26 };
    letter = (letter - m_CipherKey.keys[0]) % alphabetLength;

    if (letter < 0)
        letter += alphabetLength;
    return letter + 'A';
}

inline const char* Hill::getName()
{
    return "Hill";
}