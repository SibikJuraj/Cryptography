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
    int numberOfLetters(const std::string_view& text)
    {
        if (text.size() == 0)
            return 0;

        int letterCount{ 0 };
        for (int i{ 0 }; i < text.length(); ++i)
        {
            if (text[i] == '\0')
                break;

            if (text[i] >= 'a' && text[i] <= 'z' || text[i] >= 'A' && text[i] <= 'Z')
                ++letterCount;
        }
        return letterCount;
    }

    AnalysisOfText analyzeText(const std::string_view& text)
    {
        if (text.size() == 0)
            throw std::exception();

        auto analysis{ AnalysisOfText() };

        for (char letter : text)
        {
            if (letter == '\0')
                break;

            letter = toupper(letter);
            if (letter >= 'A' && letter <= 'Z')
            {
                ++analysis[letter];
                ++analysis.getNOLetters();
            }
        }

        for (char i{ 'A' }; i < 'A' + 26; ++i)
        {
            analysis[i] = ((double)analysis[i] / analysis.getNOLetters()) *
                (((double)analysis[i] - 1) / (analysis.getNOLetters() - 1));
            analysis.getIC() += analysis[i];
        }

        return analysis;
    }

	Text loadFile(const std::string_view&& path)
	{
        std::ifstream fs(path.data());

        fs.seekg(0, std::ios::end);
        fs.seekg(0, std::ios::beg);
        std::string text{ };
        text.assign((std::istreambuf_iterator<char>(fs)),
            std::istreambuf_iterator<char>());

        auto analysis{ analyzeText(text) };

        return Text(text, analysis);
	}

    std::string loadByteFile(const std::string_view&& path)
    {
        _setmode(_fileno(stdout), _O_U8TEXT);
        _setmode(_fileno(stdin), _O_U8TEXT);

        std::ifstream fs(path.data(), std::ios_base::binary);

        fs.seekg(0, std::ios::end);
        fs.seekg(0, std::ios::beg);
        std::string text{};
        text.assign((std::istreambuf_iterator<char>(fs)),
            std::istreambuf_iterator<char>());

        return text;
    }

    bool saveText(const std::string_view&& path, const std::string& text)
    {
        std::ofstream outfile;
        outfile.open(path.data());
        outfile << text;
        return true;
    }
}