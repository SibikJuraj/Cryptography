#pragma once
#include "Kasiski.h"
#include "Cipher.h"
#include <Text/TextUtils.h>
#include <Text/AnalysisOfLang.h>

struct VigenereKey
{
    std::vector<int> keys;

    VigenereKey(std::vector<int> pKeys)
        : keys{ pKeys } {}
};

class Vigenere : public Cipher<VigenereKey, std::string>
{
public:
	Vigenere();
    virtual std::string encrypt(const std::string& input) override;
    virtual std::string decrypt(const std::string& input) override;
    virtual std::string update(const std::string& input) override;
    virtual bool tryFindKey(const std::string& input) override;
    virtual const char* getName() override;
private:
	char encryptingFormula(char letter);
	char decryptingFormula(char letter);
	int m_Counter;
};

inline Vigenere::Vigenere()
    : Cipher(VigenereKey(std::vector<int>(1))), m_Counter{ 0 }
{
}

inline std::string Vigenere::update(const std::string& input)
{
    return m_CipherMode == MODE_DECRYPT ? decrypt(input) : encrypt(input);
}

inline std::string Vigenere::encrypt(const std::string& input)
{
    throw std::logic_error("Not implemented");
}

inline std::string Vigenere::decrypt(const std::string& input)
{
    m_CipherMode = MODE_DECRYPT;
    const AnalysisOfSKLang language{};
    m_Counter = 0;

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
    if (!TextUtils::isLetter(letter))
        return letter;
    bool lower{ TextUtils::toUpperCase(letter) };
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

inline bool Vigenere::tryFindKey(const std::string& input)
{
    if (input.size() == 0)
        return false;

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
        std::vector<std::string> outputParts{ TextUtils::sliceText(input, potentialPassLength) };

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

    std::vector<std::string> outputParts{ TextUtils::sliceText(input, passLength) };
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
    return true;
}