#include "Text.h"
#include <fstream>
#include <sstream>
#include <array>

Text::Text()
    : m_Text{ std::make_unique<std::string>()}, m_Spaces{ std::make_unique<std::vector<int>>() },
    m_AnalysisOfText{ std::make_unique<AnalysisOfText>() }
{
}

Text::Text(std::unique_ptr<std::string> text, std::unique_ptr<std::vector<int>> spaces,
    std::unique_ptr<AnalysisOfText> analysis)
    : m_Text{ std::move(text) }, m_Spaces{ std::move(spaces) },m_AnalysisOfText{ std::move(analysis) }
{
}

Text::Text(const Text& other)
    : m_Text{ std::make_unique<std::string>(*other.m_Text) },
    m_Spaces{ std::make_unique<std::vector<int>>(*other.m_Spaces) },
    m_AnalysisOfText{ std::make_unique<AnalysisOfText>(*other.m_AnalysisOfText)}
{
}

std::string Text::textWithSpaces()
{
    std::string textWithSpaces{*m_Text};
    for (int index : *m_Spaces)
    {
        textWithSpaces.insert(index, " ");
    }
    return textWithSpaces;
}

std::string& Text::getText()
{
    return *m_Text;
}

AnalysisOfText& Text::getTextAnalysis()
{
    return *m_AnalysisOfText;
}

const AnalysisOfText& Text::getTextAnalysis() const
{
    return *m_AnalysisOfText;
}

const std::string& Text::getText() const
{
    return *m_Text;
}
