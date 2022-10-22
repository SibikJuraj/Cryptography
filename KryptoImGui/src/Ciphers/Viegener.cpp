#include "Viegener.h"
#include "Text/Kasiski.h"

#include <array>
#include <algorithm>

constexpr double c_SkCoincidenceIndex{ 0.06027 };

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
    int index{ 0 };

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

                ic += outputParts[k].getAlphabet().m_IC;
            }
            ic = ic / passLength;
            if (abs(ic - c_SkCoincidenceIndex) < 0.01 &&
                abs(ic - c_SkCoincidenceIndex) < abs(maxIc - c_SkCoincidenceIndex))
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
            std::vector<std::pair<int, double>> popularLetters{};

            for (int i{ 0 }; i < Alphabet::alphabet_length; ++i)
            {
                if (outputParts[k].getAlphabet().m_LetterIC[i] > 0.003)
                {
                    popularLetters.push_back({ i, outputParts[k].getAlphabet().m_LetterIC[i] });
                }
            }

            int moveIndex{ 0 };

            for (int i{ 0 }; i <= popularLetters.size(); ++i)
            {
                if (popularLetters.size() >= 3)
                {
                    if ((popularLetters[0].first + 4) % Alphabet::alphabet_length == popularLetters[1].first &&
                        (popularLetters[1].first + 4) % Alphabet::alphabet_length == popularLetters[2].first)
                    {
                        moveIndex = popularLetters[0].first;
                        break;
                    }
                }
                std::rotate(popularLetters.begin(), popularLetters.begin() + 1, popularLetters.end());
            }
            if (moveIndex == 0)
            {
                for (int i{ 0 }; i <= popularLetters.size(); ++i)
                {
                    if (popularLetters.size() >= 2)
                    {
                        if ((popularLetters[0].first + 4) % Alphabet::alphabet_length == popularLetters[1].first)
                        {
                            moveIndex = abs(4 - popularLetters[0].first);
                            break;
                        }
                        if (popularLetters[1].first - popularLetters[0].first == 1)
                        {
                            moveIndex = abs(13 - popularLetters[0].first);
                            break;
                        }
                    }

                    std::rotate(popularLetters.begin(), popularLetters.begin() + 1, popularLetters.end());
                }
            }
            m_Keys[k] = moveIndex;
        }
    }

    Text output{ input };
    for (int i{ 0 }; i < input.getText().size(); ++i)
        output.getText()[i] = cryptingFormula(output.getText()[i]);

    std::string password{};
    for (int i{ 0 }; i < m_Keys.size(); ++i)
    {
        char letter{ static_cast<char>((m_Keys[i] < 0 ? m_Keys[i] + Alphabet::alphabet_length: m_Keys[i]) % Alphabet::alphabet_length) + 65 };

        password.push_back(letter);

    }

    output.getText().append("\n\nPassword: " + password + " length: " + std::to_string(m_Keys.size()));
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
