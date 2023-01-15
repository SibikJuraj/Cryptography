#pragma once
#include "Kasiski.h"

struct VigenereKey
{
    std::vector<int> keys;

    VigenereKey(std::vector<int> pKeys)
        : keys{ pKeys } {}
};

class Vigenere : public Cipher<VigenereKey>
{
public:
	Vigenere();
	virtual std::string encrypt(const std::string_view input) override;
	virtual std::string decrypt(const std::string_view input) override;
    virtual std::string update(const std::string_view input) override;
    virtual const char* getName() override;
protected:
	virtual char encryptingFormula(char letter) override;
	virtual char decryptingFormula(char letter) override;
private:
	int m_Counter;
};

inline Vigenere::Vigenere()
    : Cipher(VigenereKey(std::vector<int>())), m_Counter{ 0 }
{
}

inline std::string Vigenere::update(const std::string_view input)
{
    m_Counter = 0;
    const AnalysisOfSKLang language{};
    std::string output{};
    for (int i{ 0 }; i < input.size(); ++i)
    {
        if (m_CipherMode == MODE_DECRYPT)
            output += decryptingFormula(input[i]);
        else
            output += encryptingFormula(input[i]);
    }
    output += "\n\nPassword: ";
    for (int i{ 0 }; i < m_CipherKey.keys.size(); ++i)
        output += (static_cast<char>((m_CipherKey.keys[i] < 0 ? m_CipherKey.keys[i] + language.getAlphabetLength()
            : m_CipherKey.keys[i]) % language.getAlphabetLength()) + 65);
    output += " length: " + std::to_string(m_CipherKey.keys.size());

    return output;
}

inline std::string Vigenere::encrypt(const std::string_view input)
{
    throw std::logic_error("Not implemented");
}

inline std::string Vigenere::decrypt(const std::string_view input)
{
    m_CipherMode = MODE_DECRYPT;

    m_Counter = 0;
    int passLength{ 0 };
    const AnalysisOfSKLang language{};

    double maxIc{ 0.0 };
    double ic{ 0.0 };

    // Dlzka hesla
    std::vector<int> potentialPassLengths{ Kasiski::getPasswordLengths(input) };
    for (int potentialPassLength : potentialPassLengths)
    {
        if (potentialPassLength == 0)
            break;
        ic = 0.0;
        std::vector<std::string> outputParts{ Text::sliceText(input, potentialPassLength) };

        for (int k{ 0 }; k < outputParts.size(); ++k)
            ic += AnalysisOfText{ outputParts[k] }.getIC();

        ic = ic / potentialPassLength;
        if (abs(ic - language.getIC()) < 0.01 &&
            abs(ic - language.getIC()) < abs(maxIc - language.getIC()))
        {
            maxIc = ic;
            passLength = potentialPassLength;
        }
    }
    m_CipherKey.keys.resize(passLength);

    std::vector<std::string> outputParts{ Text::sliceText(input, passLength) };
    // Euklidova vzdialenost
    for (int k{ 0 }; k < m_CipherKey.keys.size(); ++k)
    {
        AnalysisOfText outputAnalysis{ outputParts[k] };

        double minDist{ 10.00 };

        for (int j{ 0 }; j <= language.getAlphabetLength(); ++j)
        {
            double dist{ 0.0 };
            for (char i{ 'A' }; i < 'A' + language.getAlphabetLength(); ++i)
                dist += pow(language[i] - outputAnalysis[i], 2);

            dist = sqrt(dist);
            if (dist < minDist)
            {
                minDist = dist;
                m_CipherKey.keys[k] = j;
            }
            outputAnalysis.rotateLetters();
        }
    }

    std::string output{};
    for (int i{ 0 }; i < input.size(); ++i)
        output += decryptingFormula(input[i]);
    output += "\n\nPassword: ";
    for (int i{ 0 }; i < m_CipherKey.keys.size(); ++i)
        output += (static_cast<char>((m_CipherKey.keys[i] < 0 ? m_CipherKey.keys[i] + language.getAlphabetLength() : m_CipherKey.keys[i]) % language.getAlphabetLength()) + 65 );
    output += " length: " + std::to_string(m_CipherKey.keys.size());

    return output;
}

inline char Vigenere::encryptingFormula(char letter)
{
    throw std::logic_error("Not implemented");
}

inline char Vigenere::decryptingFormula(char letter)
{
    if (!Text::isLetter(letter))
        return letter;
    bool lower{ Text::toUpperCase(letter) };
    letter -= 'A';
    int alphabetLength{ 26 };
    letter = (letter - m_CipherKey.keys[m_Counter]) % alphabetLength;
    m_Counter = ++m_Counter % m_CipherKey.keys.size();

    if (letter < 0)
        letter += alphabetLength;

    return !lower ? letter + 'A' : letter + 'a';
}

inline const char* Vigenere::getName()
{
    return "Vigenere";
}