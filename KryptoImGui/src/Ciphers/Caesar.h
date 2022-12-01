#pragma once
#include <Ciphers/Cipher.h>

class Caesar : public CipherCore<int>
{
public:
	Caesar();
	virtual Text encrypt(const Text& input, bool fineTuning) override;
	virtual Text decrypt(const Text& input, bool fineTuning) override;
	virtual char encryptingFormula(char letter) override;
	virtual char decryptingFormula(char letter) override;
};

inline Caesar::Caesar()
    : Cipher(std::vector<int>(1))
{
}

inline Text Caesar::encrypt(const Text& input, bool fineTuning)
{
    Text output(input);
    for (int i{ 0 }; i < output.getText().size(); ++i)
    {
        output.getText()[i] = encryptingFormula(output.getText()[i]);
    }
    output.analyzeText();
    return output;
}

inline Text Caesar::decrypt(const Text& input, bool fineTuning)
{
    Text output(input);
    if (!fineTuning)
    {
        double max{ -1.0 };
        int alphabetLength{ 26 };
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
    output.analyzeText();
    return output;
}

inline char Caesar::encryptingFormula(char letter)
{
    letter -= 'A';
    int alphabetLength{ 26 };
    letter = (letter + m_Keys[0]) % alphabetLength;

    if (letter < 0)
        letter += alphabetLength;
    return letter + 'A';
}

inline char Caesar::decryptingFormula(char letter)
{
    letter -= 'A';
    int alphabetLength{ 26 };
    letter = (letter - m_Keys[0]) % alphabetLength;

    if (letter < 0)
        letter += alphabetLength;
    return letter + 'A';
}
