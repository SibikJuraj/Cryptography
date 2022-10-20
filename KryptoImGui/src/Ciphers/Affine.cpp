#include "Affine.h"

Affine::Affine(CryptingMode mode)
    : Cipher(std::vector<int>(2), mode)
{
}

void Affine::encrypt(Text& output, bool fineTuning)
{
    for (int i{ 0 }; i < output.getText().size(); ++i)
    {
        output.getText()[i] = cryptingFormula(output.getText()[i]);
    }
}

void Affine::decrypt(Text& output, bool fineTuning)
{
    for (int i{ 0 }; i < output.getText().size(); ++i)
    {
        output.getText()[i] = cryptingFormula(output.getText()[i]);
    }
}

char Affine::cryptingFormula(char letter)
{
    letter -= 'A';
    if (m_Mode == CryptingMode::encrypt)
        letter = (m_Keys[0] * letter + m_Keys[1]) % Alphabet::alphabet_length;
    else
        letter = (m_Keys[0] * letter - m_Keys[1]) % Alphabet::alphabet_length;

    if (letter < 0)
        letter += Alphabet::alphabet_length;
    return letter + 'A';
}
