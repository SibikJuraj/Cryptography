#pragma once
#include <Ciphers/Cipher.h>
#include "Kasiski.h"

class Viegener : public CipherCore<int>
{
public:
	Viegener();
	virtual Text encrypt(const Text& input) override;
	virtual Text decrypt(const Text& input) override;
	virtual char encryptingFormula(char letter) override;
	virtual char decryptingFormula(char letter) override;
private:
	int m_Counter;
};

inline Viegener::Viegener()
    : CipherCore(std::vector<int>{}), m_Counter{ 0 }
{
}

inline Text Viegener::encrypt(const Text& input)
{
    throw std::logic_error("Not implemented");
}

inline Text Viegener::decrypt(const Text& input)
{
    std::string_view rawText{ input.getRawText() };

    m_Counter = 0;
    int passLength{ 0 };
    const AnalysisOfSKLang language{};

    double maxIc{ 0.0 };
    double ic{ 0.0 };
    std::vector<int> potentialPassLengths{ Kasiski::getPasswordLengths(rawText) };
    for (int potentialPassLength : potentialPassLengths)
    {
        if (potentialPassLength == 0)
            break;
        m_Keys.resize(potentialPassLength);
        ic = 0.0;
        std::vector<Text> outputParts(potentialPassLength);
        input.sliceText(outputParts);

        for (int k{ 0 }; k < outputParts.size(); ++k)
            ic += outputParts[k].getTextAnalysis().getIC();

        ic = ic / potentialPassLength;
        if (abs(ic - language.getIC()) < 0.01 &&
            abs(ic - language.getIC()) < abs(maxIc - language.getIC()))
        {
            maxIc = ic;
            passLength = potentialPassLength;
        }
    }

    m_Keys.resize(passLength);

    std::vector<Text> outputParts(m_Keys.size());
    input.sliceText(outputParts);

    for (int k{ 0 }; k < m_Keys.size(); ++k)
    {
        double minDist{ 10.00 };

        for (int j{ 0 }; j <= language.getAlphabetLength(); ++j)
        {
            double dist{ 0.0 };
            for (char i{ 'A' }; i < 'A' + language.getAlphabetLength(); ++i)
                dist += pow(language[i] - outputParts[k].getTextAnalysis()[i], 2);

            dist = sqrt(dist);
            if (dist < minDist)
            {
                minDist = dist;
                m_Keys[k] = j;
            }
            outputParts[k].getTextAnalysis().rotateLetters();
        }
    }


    Text output;
    for (int i{ 0 }; i < rawText.size(); ++i)
        output.addLetter(decryptingFormula(rawText[i]));

    std::string password{};
    for (int i{ 0 }; i < m_Keys.size(); ++i)
    {
        char letter{ static_cast<char>((m_Keys[i] < 0 ? m_Keys[i] + language.getAlphabetLength() : m_Keys[i]) % language.getAlphabetLength()) + 65 };

        password.push_back(letter);

    }
    output.addText("\n\nPassword: " + password + " length: " + std::to_string(m_Keys.size()));

    return output;
}

inline char Viegener::encryptingFormula(char letter)
{
    throw std::logic_error("Not implemented");
}

inline char Viegener::decryptingFormula(char letter)
{
    letter -= 'A';
    int alphabetLength{ 26 };
    letter = (letter - m_Keys[m_Counter]) % alphabetLength;
    m_Counter = ++m_Counter % m_Keys.size();

    if (letter < 0)
        letter += alphabetLength;
    return letter + 'A';
}
