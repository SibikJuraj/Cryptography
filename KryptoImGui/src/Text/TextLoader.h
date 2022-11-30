#pragma once

#include <memory>
#include <string_view>
#include <fstream>
#include <sstream>

#include "AnalysisOfLang.h"
#include "Class Text/Text.h"


#include <io.h>
#include <fcntl.h>

namespace TextLoader
{
    std::unique_ptr<std::vector<int>> removeSpaces(std::string& text)
    {
        int i{ 0 };
        auto spaces{ std::make_unique<std::vector<int>>() };
        for (char letter : text)
        {
            if (letter == ' ')
            {
                spaces->push_back(i);
            }
            ++i;
        }
        text.erase(std::remove_if(text.begin(), text.end(), ::isspace),
            text.end());

        return spaces;
    }

    std::unique_ptr<AnalysisOfText> analyzeText(const std::string_view& text)
    {
        _setmode(_fileno(stdout), _O_U8TEXT);
        _setmode(_fileno(stdin), _O_U8TEXT);

        if (text.size() == 0)
            return nullptr;

        auto analysis{ std::make_unique<AnalysisOfText>() };

        for (char letter : text)
        {
            if (letter == '\0')
                break;

            letter = toupper(letter);
            if (letter >= 'A' && letter <= 'Z')
            {
                ++(*analysis)[letter];
                ++analysis->getNOLetters();
            }
        }

        for (char i{ 'A' }; i < 'A' + 26; ++i)
        {
            (*analysis)[i] = (((double)(*analysis)[i] / analysis->getNOLetters())) *
                (((double)(*analysis)[i] - 1) / (analysis->getNOLetters() - 1));

            analysis->getIC() += (*analysis)[i];
        }

        return analysis;
    }

	std::unique_ptr<Text> loadFile(const std::string_view&& path)
	{
        std::ifstream fs(path.data());

        fs.seekg(0, std::ios::end);
        auto text{std::make_unique<std::string>()};
        fs.seekg(0, std::ios::beg);
        text->assign((std::istreambuf_iterator<char>(fs)),
            std::istreambuf_iterator<char>());

        auto spaces{ removeSpaces(*text) };
        auto analysis{ analyzeText(*text) };

        return std::make_unique<Text>(std::move(text), std::move(spaces), std::move(analysis));
	}

    char* loadByteFile(const std::string_view&& path)
    {
        std::ifstream fs(path.data());

        fs.seekg(0, std::ios::end);
        auto length{ fs.tellg() };
        char* text{ new char[length] };
        fs.seekg(0, std::ios::beg);

        fs.read(text, length);

        return text;
    }

    bool saveText(const std::string_view&& path, const std::string& text)
    {
        std::ofstream outfile;
        outfile.open(path.data(), std::ios_base::app);//std::ios_base::app
        outfile << text;
        return true;
    }
}