#include "Text.h"
#include <fstream>
#include <sstream>

Text::Text(int alphabetLength)
    : m_Alphabet{ loadAlphabet(alphabetLength) }
{
}

Text::Text(std::string_view pathToAlphabet)
    : m_Alphabet{ loadAlphabet(pathToAlphabet) }
{
    loadText("texts/text.txt");
}

Text::Text(const Text& other)
    : m_Text{other.m_Text}, m_Alphabet{other.m_Alphabet}
{
}

bool Text::loadText(std::string_view path)
{
    try
    {
        std::ifstream fs(path.data());

        fs.seekg(0, std::ios::end);
        m_Text.reserve(10000);
        fs.seekg(0, std::ios::beg);
        m_Text.assign((std::istreambuf_iterator<char>(fs)),
            std::istreambuf_iterator<char>());
        return true;
    }
    catch (...)
    {
        return false;
    }
}

Alphabet Text::loadAlphabet(int alphabetLength)
{
    double ic{};
    std::vector<std::pair<char, double>> alphabet(alphabetLength);
    return Alphabet{ alphabet, ic };
}

Alphabet Text::loadAlphabet(std::string_view path)
{
    double ic{};
    std::vector<std::pair<char, double>> alphabet{};

    std::string line;
    std::ifstream myfile(path.data());
    while (std::getline(myfile, line)) {       // cache the line
        if (line.size() >= 2 && line[1] == ';')
        {
            double c{ stod(line.substr(2, line.size() - 2)) };
            alphabet.push_back(std::make_pair(line[0], c));
        }
        else
            ic = stod(line);
    }
    return Alphabet{ alphabet, ic };
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
    m_Text.erase(std::remove_if(m_Text.begin(), m_Text.end(), ::isspace),
        m_Text.end());
}

void Text::sliceText(std::vector<std::string>& parts)
{
    for (int i{ 0 }; i < parts.size(); ++i)
        parts[i].reserve(std::ceil((double)m_Text.size() / parts.size()));

    int part{ 0 };
    for (auto letter : m_Text)
    {
        parts[part] += letter;
        part = ++part % parts.size();
    }
}

std::string& Text::getText()
{
    return m_Text;
}

Alphabet& Text::getAlphabet()
{
    return m_Alphabet;
}
