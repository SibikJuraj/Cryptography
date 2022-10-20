#include "Caesar.h"
#include <string>


Caesar::Caesar(CryptingMode mode)
    : Cipher(std::vector<int>(1), mode)
{
}

void Caesar::encrypt(Text& output, bool fineTuning)
{
    for (int i{ 0 }; i < output.getText().size(); ++i)
    {
        output.getText()[i] = cryptingFormula(output.getText()[i]);
    }
}

void Caesar::decrypt(Text& output, bool fineTuning)
{
    for (int i{ 0 }; i < output.getText().size(); ++i)
    {
        output.getText()[i] = cryptingFormula(output.getText()[i]);
    }
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
