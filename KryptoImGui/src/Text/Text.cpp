#include "Text.h"
#include <fstream>
#include <sstream>
#include <array>

#include "Engine/Core/Application.h"

Text::Text()
    : m_Text{}, m_Spaces{},
    m_AnalysisOfText{}
{
}

Text::Text(std::string_view path)
    : m_AnalysisOfText{}
{
    std::ifstream fs(path.data());

    fs.seekg(0, std::ios::end);
    m_Text.reserve(10000);
    fs.seekg(0, std::ios::beg);
    m_Text.assign((std::istreambuf_iterator<char>(fs)),
        std::istreambuf_iterator<char>());

    removeSpaces();
    analyzeText();
}

Text::Text(const Text& other)
    : m_Text{other.m_Text}, m_AnalysisOfText{other.m_AnalysisOfText },
    m_Spaces {other.m_Spaces}
{
}

void Text::analyzeText()
{
    if (m_Text.size() == 0)
        return;

    for (char letter : m_Text)
    {
        if (letter == '\n')
            break;
        ++m_AnalysisOfText[letter];
    }

    for (char i{'A'}; i < 'A' + 26; ++i)
    {
        m_AnalysisOfText[i] = ((double)m_AnalysisOfText[i] / m_Text.size()) *
            ((double)(m_AnalysisOfText[i] - 1) / (m_Text.size() - 1));

        m_AnalysisOfText.getIC() += m_AnalysisOfText[i];
    }
}

bool Text::saveText(std::string_view path)
{
    std::ofstream outfile;
    outfile.open(path.data(), std::ios_base::app);//std::ios_base::app
    outfile << m_Text;
    return true;
}

void Text::removeSpaces()
{
    int i{ 0 };
    for (char& letter : m_Text)
    {
        if (letter == ' ')
        {
            m_Spaces.push_back(i);
        }
        ++i;
    }
    m_Text.erase(std::remove_if(m_Text.begin(), m_Text.end(), ::isspace),
        m_Text.end());
}

std::string Text::textWithSpaces()
{
    std::string textWithSpaces{m_Text};
    for (int index : m_Spaces)
    {
        textWithSpaces.insert(index, " ");
    }
    return textWithSpaces;
}

void Text::sliceText(std::vector<Text>& parts) const
{
    for (int i{ 0 }; i < parts.size(); ++i)
        parts[i].getText().reserve(std::ceil((double)m_Text.size() / parts.size()));

    int part{ 0 };
    for (auto letter : m_Text)
    {
        parts[part].getText() += letter;
        part = ++part % parts.size();
    }
}

std::string& Text::getText()
{
    return m_Text;
}

AnalysisOfText& Text::getTextAnalysis()
{
    return m_AnalysisOfText;
}

const AnalysisOfText& Text::getTextAnalysis() const
{
    return m_AnalysisOfText;
}

const std::string& Text::getText() const
{
    return m_Text;
}