#include "Text.h"
#include <fstream>
#include <sstream>
#include <array>

Text::Text()
    : m_Text{ }, m_AnalysisOfText{ }, m_RawText{ }
{
}

Text::Text(std::string text, AnalysisOfText analysis)
    : m_Text{ text }, m_AnalysisOfText{ analysis }, m_RawText{}
{
    createRawText();
}

Text::Text(const Text& other)
    : m_Text{ other.m_Text }, m_AnalysisOfText{ other.m_AnalysisOfText }, m_RawText{ other.m_RawText }
{
}

const AnalysisOfText& Text::getTextAnalysis() const
{
    return m_AnalysisOfText;
}

const std::string& Text::getText() const
{
    return m_Text;
}

void Text::addLetter(char letter)
{

}

void Text::removeLetter()
{
}

void Text::createRawText()
{
    for (char letter : m_Text)
    {
        if (letter == '\0')
            break;

        if (letter >= 'a' && letter <= 'z')
            letter = toupper(letter);
        if (letter >= 'A' && letter <= 'Z')
            m_RawText += letter;
    }
}
