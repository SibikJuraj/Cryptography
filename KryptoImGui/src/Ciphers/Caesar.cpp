#include "Caesar.h"
#include <string>


Caesar::Caesar(std::vector<int> keys, CryptingMode mode)
    : Cipher(keys, mode)
{
}

void Caesar::encrypt(Text& output, bool fineTuning)
{
    for (int i{ 0 }; i < output.getText().size(); ++i)
    {
        output.getText()[i] = cryptingFormula(output.getText()[i], output.getAlphabet().m_Alphabet.size());
    }
}

void Caesar::decrypt(Text& output, bool fineTuning)
{
    for (int i{ 0 }; i < output.getText().size(); ++i)
    {
        output.getText()[i] = cryptingFormula(output.getText()[i], output.getAlphabet().m_Alphabet.size());
    }
}

char Caesar::cryptingFormula(char letter, int alphabetLength)
{
    if (m_Mode == CryptingMode::encrypt)
        return letter - 'A' + m_Keys[0] % alphabetLength + 'A';
    else
        return letter - 'A' - m_Keys[0] % alphabetLength + 'A';
}
