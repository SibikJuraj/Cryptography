#include "Affine.h"

Affine::Affine(CryptingMode mode)
    : Cipher(std::vector<int>(2), mode)
{
}

Text Affine::encrypt(const Text& input, bool fineTuning)
{
    Text output(input);
    for (int i{ 0 }; i < output.getText().size(); ++i)
    {
        output.getText()[i] = cryptingFormula(output.getText()[i]);
    }
    return output;
}

Text Affine::decrypt(const Text& input, bool fineTuning)
{
    Text output(input);
    for (int i{ 0 }; i < output.getText().size(); ++i)
    {
        output.getText()[i] = cryptingFormula(output.getText()[i]);
    }
    return output;
}

char Affine::cryptingFormula(char letter)
{
    letter -= 'A';
    if (Alphabet::alphabet_length == 26)
    {
        if (m_Keys[0] % 2 == 1 && m_Keys[0] != 13)
        {
            if (m_Mode == CryptingMode::encrypt)
                letter = (m_Keys[0] * letter + m_Keys[1]) % Alphabet::alphabet_length;
            else
                letter = (m_Keys[0] * (letter - m_Keys[1])) % Alphabet::alphabet_length;
        }
    }

    if (letter < 0)
        letter += Alphabet::alphabet_length;
    return letter + 'A';
}
