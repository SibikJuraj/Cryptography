#include "Viegener.h"
#include "Text/Kasiski.h"

#include <array>
#include <algorithm>


Viegener::Viegener()
	: Cipher(std::vector<int>{}), m_Counter{0}
{
}

Text Viegener::encrypt(const Text& input, bool fineTuning)
{
    m_Counter = 0;
    Text output(input);
    for (int i{ 0 }; i < output.getText().size(); ++i)
    {
        output.getText()[i] = cryptingFormula(output.getText()[i]);
    }
    return output;
}

Text Viegener::decrypt(const Text& input, bool fineTuning)
{
    m_Counter = 0;
    int index{ 0 };
    Alphabet language = input.getLanguage();

    if (!fineTuning)
    {
        std::vector<int> passLengths{ Kasiski::getPasswordLengths(input) };
        double maxIc{ 0.0 };
        double ic{ 0.0 };
        for (int passLength : passLengths)
        {
            if (passLength == 0)
                break;
            ic = 0.0;
            std::vector<Text> outputParts(passLength);
            input.sliceText(outputParts);
            m_Keys.resize(passLength);

            //output.getText().append("\nPassword length: " + std::to_string(passLength));
            for (int k{0}; k < outputParts.size(); ++k)
            {
                outputParts[k].analyzeText();
                //output.getText().append("\nCoincidence index: " + std::to_string(outputParts[k].getAlphabet().m_IC));

                ic += outputParts[k].getAlphabet().m_IC;
            }
            ic = ic / passLength;
            if (abs(ic - language.m_IC) < 0.01 &&
                abs(ic - language.m_IC) < abs(maxIc - language.m_IC))
            {
                maxIc = ic;
                index = passLength;
            }
            //output.getText().append("\nIndex of coincidence: " + std::to_string(ic) + '\n');
        }


        m_Keys.resize(index);

        std::vector<Text> outputParts(m_Keys.size());
        input.sliceText(outputParts);

        for (int k{ 0 }; k < m_Keys.size(); ++k)
        {
            outputParts[k].analyzeText();
            double minDist{ 10.00 };

            for (int j{ 0 }; j <= Alphabet::alphabet_length; ++j)
            {
                double dist{ 0.0 };
                for (int i{ 0 }; i < Alphabet::alphabet_length; ++i)
                {
                    dist += pow(language.m_LetterIC[i] - outputParts[k].getAlphabet().m_LetterIC[i], 2);
                }
                dist = sqrt(dist);
                if (dist < minDist)
                {
                    minDist = dist;
                    m_Keys[k] = j;
                }
                std::rotate(outputParts[k].getAlphabet().m_LetterIC.begin(), outputParts[k].getAlphabet().m_LetterIC.begin() + 1, outputParts[k].getAlphabet().m_LetterIC.end());
            }
            outputParts[k].analyzeText();
        }
    }

    Text output{ input };
    for (int i{ 0 }; i < input.getText().size(); ++i)
        output.getText()[i] = cryptingFormula(output.getText()[i]);

    std::string password{};
    for (int i{ 0 }; i < m_Keys.size(); ++i)
    {
        char letter{ static_cast<char>((m_Keys[i] < 0 ? m_Keys[i] + Alphabet::alphabet_length: m_Keys[i]) % Alphabet::alphabet_length) + 65 };

        password.push_back(letter);

    }

    output.getText().append("\n\nPassword: " + password + " length: " + std::to_string(m_Keys.size()));
    return output;
}

char Viegener::cryptingFormula(char letter)
{
    letter -= 'A';
    if (m_Mode == CryptingMode::encrypt)
        letter = (letter + m_Keys[m_Counter]) % Alphabet::alphabet_length;
    else
        letter = (letter - m_Keys[m_Counter]) % Alphabet::alphabet_length;

    m_Counter = ++m_Counter % m_Keys.size();
    if (letter < 0)
        letter += Alphabet::alphabet_length;
    return letter + 'A';
}
