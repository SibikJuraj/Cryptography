#include "Caesar.h"
#include <string>


Caesar::Caesar(CryptingMode mode)
    : Cipher(std::vector<int>(1), mode)
{
}

Text Caesar::encrypt(const Text& input, bool fineTuning)
{
    Text output(input);
    for (int i{ 0 }; i < output.getText().size(); ++i)
    {
        output.getText()[i] = cryptingFormula(output.getText()[i]);
    }
    return output;
}

Text Caesar::decrypt(const Text& input, bool fineTuning)
{
    Text output(input);
    double max{-1.0};
    for (int i{0}; i < output.getAlphabet().m_LetterIC.size(); ++i)
    {
        if (max < output.getAlphabet().m_LetterIC[i])
        {
            max = output.getAlphabet().m_LetterIC[i];
            m_Keys[0] = i;
        }
    }
    for (int i{ 0 }; i < output.getText().size(); ++i)
    {
        output.getText()[i] = cryptingFormula(output.getText()[i]);
    }
    return output;
}

char Caesar::cryptingFormula(char letter)
{
    letter -= 'A';
    if (m_Mode == CryptingMode::encrypt)
        letter = (letter + m_Keys[0]) % Alphabet::alphabet_length;
    else
        letter = (letter - m_Keys[0]) % Alphabet::alphabet_length;
    
    if (letter < 0)
        letter += Alphabet::alphabet_length;
    return letter + 'A';
}
