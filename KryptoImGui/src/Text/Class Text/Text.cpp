#include "Text.h"
#include <fstream>
#include <sstream>
#include <array>

int Text::letterCount(std::string_view text)
{
    auto lCount{ 0 };
    for (int i{ 0 }; i < text.length(); ++i)
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
            ++lCount;
    return lCount;
}

Text::Text()
    : m_Text{ }, m_AnalysisOfText{ }, m_RawText{ }
{
}

Text::Text(std::string text)
    : m_Text{ text }, m_AnalysisOfText{ }, m_RawText{ }
{
    createRawText();
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

AnalysisOfText& Text::getTextAnalysis()
{
    return m_AnalysisOfText;
}

const std::string_view& Text::getText() const
{
    return m_Text;
}

const std::string_view& Text::getRawText() const
{
    return m_RawText;
}

void Text::sliceText(std::vector<Text>& parts) const
{
    int part{ 0 };
    for (auto letter : m_RawText)
    {
        parts[part].addLetter(letter);
        part = ++part % parts.size();
    }
}

void Text::addLetter(char letter)
{
    m_Text += letter;
    if (letter >= 'a' && letter <= 'z')
        letter = toupper(letter);
    if (letter >= 'A' && letter <= 'Z')
    {
        m_RawText += letter;
        m_AnalysisOfText.addLetter(letter);
        m_AnalysisOfText.updateStatistics();
    }
}

void Text::changeLetter(char letter, int index)
{
    if (m_Text.size() == 0)
        return;

    m_Text[index] = letter;
    if (m_RawText.size() != 0)
    {
        auto last{ m_Text.size() - 1 };
        auto rLast{ m_RawText.size() - 1 };
        if (m_Text[last] == m_RawText[rLast] || m_Text[last] == tolower(m_RawText[rLast]))
        {
            m_AnalysisOfText.removeLetter(m_RawText[rLast]);
            m_AnalysisOfText.updateStatistics();
            m_RawText.pop_back();
        }
    }

}

void Text::addText(const std::string_view text)
{
    for (char letter : text)
        addLetter(letter);
}

void Text::removeLetter()
{
    if (m_Text.size() == 0)
        return;

    if (m_RawText.size() != 0)
    {
        auto last{ m_Text.size() - 1 };
        auto rLast{ m_RawText.size() - 1 };
        if (m_Text[last] == m_RawText[rLast] || m_Text[last] == tolower(m_RawText[rLast]))
        {
            m_AnalysisOfText.removeLetter(m_RawText[rLast]);
            m_AnalysisOfText.updateStatistics();
            m_RawText.pop_back();
        }
    }

    m_Text.pop_back();
}

void Text::createRawText()
{
    if (!m_RawText.empty())
        return;
    for (char letter : m_Text)
    {
        if (letter == '\0')
            break;

        if (letter >= 'a' && letter <= 'z')
            letter = toupper(letter);
        if (letter >= 'A' && letter <= 'Z')
        {
            m_RawText += letter;
            m_AnalysisOfText.addLetter(letter);
        }
    }
    m_AnalysisOfText.updateStatistics();
}

