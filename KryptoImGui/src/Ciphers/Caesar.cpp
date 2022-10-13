#include "Caesar.h"
#include <string>

Caesar::Caesar()
    : m_K1{0}
{
}

Caesar::~Caesar()
{
}

std::string Caesar::encrypt(const std::string_view& text)
{
    return text.data();
}

std::string Caesar::decrypt(const std::string_view& text)
{
    std::string decryptedText;
    for (int i{ 0 }; i < text.size(); ++i)
    {
        decryptedText.push_back(text[i] - 'A' - m_K1 % 26 + 'A');
    }

    return decryptedText;
}
