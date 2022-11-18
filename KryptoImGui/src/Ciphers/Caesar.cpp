#include "Caesar.h"

Caesar::Caesar()
    : Cipher(std::vector<int>(1))
{
}

Text Caesar::encrypt(const Text& input, bool fineTuning)
{
    Text output(input);
    for (int i{ 0 }; i < output.getText().size(); ++i)
    {
        output.getText()[i] = encryptingFormula(output.getText()[i]);
    }
    return output;
}

Text Caesar::decrypt(const Text& input, bool fineTuning)
{
    Text output(input);
    if (!fineTuning)
    {
        double max{ -1.0 };
        int alphabetLength{ Application::getInstance().getAlphabetLength() };
        for (char i{ 'A' }; i < 'A' + alphabetLength; ++i)
        {
            if (max < output.getTextAnalysis()[i])
            {
                max = output.getTextAnalysis()[i];
                m_Keys[0] = i;
            }
        }
    }
   
    for (int i{ 0 }; i < output.getText().size(); ++i)
    {
        output.getText()[i] = decryptingFormula(output.getText()[i]);
    }
    return output;
}

char Caesar::encryptingFormula(char letter)
{
    letter -= 'A';
    int alphabetLength{ Application::getInstance().getAlphabetLength() };
    letter = (letter + m_Keys[0]) % alphabetLength;

    
    if (letter < 0)
        letter += alphabetLength;
    return letter + 'A';
}

char Caesar::decryptingFormula(char letter)
{
    letter -= 'A';
    int alphabetLength{ Application::getInstance().getAlphabetLength() };
    letter = (letter - m_Keys[0]) % alphabetLength;

    if (letter < 0)
        letter += alphabetLength;
    return letter + 'A';
}
