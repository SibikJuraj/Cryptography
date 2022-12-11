#pragma once
#include <Ciphers/Cipher.h>
#include "Kasiski.h"

class Viegener : public CipherCore<int>
{
public:
	Viegener();
	virtual std::string encrypt(const std::string_view input) override;
	virtual std::string decrypt(const std::string_view input) override;
    virtual const char* getName() override;
protected:
	virtual char encryptingFormula(char letter) override;
	virtual char decryptingFormula(char letter) override;
private:
	int m_Counter;
};

inline Viegener::Viegener()
    : CipherCore(std::vector<int>{}), m_Counter{ 0 }
{
}

inline std::string Viegener::encrypt(const std::string_view input)
{
    throw std::logic_error("Not implemented");
}

inline std::string Viegener::decrypt(const std::string_view input)
{
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
    m_Keys.resize(passLength);

    std::vector<std::string> outputParts{ Text::sliceText(input, passLength) };
    // Euklidova vzdialenost
    for (int k{ 0 }; k < m_Keys.size(); ++k)
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
                m_Keys[k] = j;
            }
            outputAnalysis.rotateLetters();
        }
    }

    std::string output{};
    for (int i{ 0 }; i < input.size(); ++i)
        output += decryptingFormula(input[i]);
    output += "\n\nPassword: ";
    for (int i{ 0 }; i < m_Keys.size(); ++i)
        output += (static_cast<char>((m_Keys[i] < 0 ? m_Keys[i] + language.getAlphabetLength() : m_Keys[i]) % language.getAlphabetLength()) + 65 );
    output += " length: " + std::to_string(m_Keys.size());

    return output;
}

inline char Viegener::encryptingFormula(char letter)
{
    throw std::logic_error("Not implemented");
}

inline char Viegener::decryptingFormula(char letter)
{
    if (!Text::isLetter(letter))
        return letter;
    bool lower{ Text::toUpperCase(letter) };
    letter -= 'A';
    int alphabetLength{ 26 };
    letter = (letter - m_Keys[m_Counter]) % alphabetLength;
    m_Counter = ++m_Counter % m_Keys.size();

    if (letter < 0)
        letter += alphabetLength;

    return !lower ? letter + 'A' : letter + 'a';
}

inline const char* Viegener::getName()
{
    return "Viegener";
}