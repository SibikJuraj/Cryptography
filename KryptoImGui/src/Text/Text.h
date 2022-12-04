#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace Text
{
    bool isLetter(char letter)
    {
        if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))
            return true;
        return false;
    }

    int toInt(char letter)
    {
        if (letter >= 'a' && letter <= 'z')
            letter = toupper(letter);
        if (letter >= 'A' && letter <= 'Z')
            return letter - 65;
        return -1;
    }

    bool toUpperCase(char& letter)
    {
        if (letter >= 'a' && letter <= 'z')
        {
            letter = toupper(letter);
            return true;
        }
        return false;
    }

    int letterCount(std::string_view text)
    {
        auto lCount{ 0 };
        for (int i{ 0 }; i < text.length(); ++i)
            if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
                ++lCount;
        return lCount;
    }

    std::vector<std::string> sliceText(const std::string_view text, int slices)
    {
        std::vector<std::string> parts(slices);
        int part{ 0 };
        for (auto letter : text)
        {
            parts[part] += letter;
            if (isLetter(letter))
                part = ++part % parts.size();
        }
        return parts;
    }
}
