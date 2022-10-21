#include "Viegener.h"
#include "Text/Kasiski.h"

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
    std::vector<int> passLengths{ Kasiski::getPasswordLengths(input) };
    m_Keys.resize(passLengths[0]);

    std::vector<Text> outputParts(passLengths[0]);
    input.sliceText(outputParts);
    if (!fineTuning)
    {
        int k{ 0 };
        for (Text& oText : outputParts)
        {
            oText.analyzeText();
            double max{ -1.0 };
            for (int i{ 0 }; i < oText.getAlphabet().m_LetterIC.size(); ++i)
            {
                if (max < oText.getAlphabet().m_LetterIC[i])
                {
                    max = oText.getAlphabet().m_LetterIC[i];
                    m_Keys[k] = i;
                }
            }
            ++k;
        }
    }
    Text output{ input };
    for (int i{ 0 }; i < input.getText().size(); ++i)
    {
        output.getText()[i] = cryptingFormula(output.getText()[i]);
    }
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
