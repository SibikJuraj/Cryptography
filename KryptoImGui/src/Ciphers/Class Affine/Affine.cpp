#include "Affine.h"

Affine::Affine()
    : Cipher(std::vector<int>(2))
{
}

Text Affine::encrypt(const Text& input, bool fineTuning)
{
    Text output(input);
    for (int i{ 0 }; i < output.getText().size(); ++i)
    {
        output.getText()[i] = encryptingFormula(output.getText()[i]);
    }
    output.analyzeText();
    return output;
}

Text Affine::decrypt(const Text& input, bool fineTuning)
{
    Text output(input);
    for (int i{ 0 }; i < output.getText().size(); ++i)
    {
        output.getText()[i] = decryptingFormula(output.getText()[i]);
    }
    output.analyzeText();
    return output;
}

char Affine::encryptingFormula(char letter)
{
    letter -= 'A';
    int alphabetLength{ 26 };
    if (alphabetLength == 26)
        if (m_Keys[0] % 2 == 1 && m_Keys[0] != 13)
            letter = (m_Keys[0] * letter + m_Keys[1]) % alphabetLength;

    if (letter < 0)
        letter += alphabetLength;
    return letter + 'A';
}

char Affine::decryptingFormula(char letter)
{
    letter -= 'A';
    int alphabetLength{ 26 };
    if (alphabetLength == 26)
        if (m_Keys[0] % 2 == 1 && m_Keys[0] != 13)
            letter = (m_Keys[0] * (letter - m_Keys[1])) % alphabetLength;

    if (letter < 0)
        letter += alphabetLength;
    return letter + 'A';
}