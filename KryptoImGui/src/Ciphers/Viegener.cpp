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
        output.getText()[i] = encryptingFormula(output.getText()[i]);
    }
    output.analyzeText();
    return output;
}

Text Viegener::decrypt(const Text& input, bool fineTuning)
{
    m_Counter = 0;
    int index{ 0 };
    const AnalysisOfLang& language = Application::getInstance().getLanguage();

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

                ic += outputParts[k].getTextAnalysis().getIC();
            }
            ic = ic / passLength;
            if (abs(ic - language.getIC()) < 0.01 &&
                abs(ic - language.getIC()) < abs(maxIc - language.getIC()))
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

            for (int j{ 0 }; j <= language.getAlphabetLength(); ++j)
            {
                double dist{ 0.0 };
                for (char i{ 'A' }; i < 'A' + language.getAlphabetLength(); ++i)
                {
                    dist += pow(language[i] - outputParts[k].getTextAnalysis()[i], 2);
                }
                dist = sqrt(dist);
                if (dist < minDist)
                {
                    minDist = dist;
                    m_Keys[k] = j;
                }
                std::rotate(outputParts[k].getTextAnalysis().getLetters().begin(), outputParts[k].getTextAnalysis().getLetters().begin() + 1, outputParts[k].getTextAnalysis().getLetters().end());
            }
            outputParts[k].analyzeText();
        }
    }

    Text output{ input };
    for (int i{ 0 }; i < input.getText().size(); ++i)
        output.getText()[i] = decryptingFormula(output.getText()[i]);

    std::string password{};
    for (int i{ 0 }; i < m_Keys.size(); ++i)
    {
        char letter{ static_cast<char>((m_Keys[i] < 0 ? m_Keys[i] + language.getAlphabetLength() : m_Keys[i]) % language.getAlphabetLength()) + 65};

        password.push_back(letter);

    }
    output.analyzeText();
    output.getText().append("\n\nPassword: " + password + " length: " + std::to_string(m_Keys.size()));
    
    return output;
}

char Viegener::encryptingFormula(char letter)
{
    letter -= 'A';
    int alphabetLength{ Application::getInstance().getAlphabetLength() };
    letter = (letter + m_Keys[m_Counter]) % alphabetLength;
    m_Counter = ++m_Counter % m_Keys.size();

    if (letter < 0)
        letter += alphabetLength;
    return letter + 'A';
}

char Viegener::decryptingFormula(char letter)
{
    letter -= 'A';
    int alphabetLength{ Application::getInstance().getAlphabetLength() };
    letter = (letter - m_Keys[m_Counter]) % alphabetLength;
    m_Counter = ++m_Counter % m_Keys.size();

    if (letter < 0)
        letter += alphabetLength;
    return letter + 'A';
}
