#include "Caesar.h"
#include <string>

Caesar::Caesar()
    : m_K1{0}
{
}

Caesar::~Caesar()
{
}

const char* Caesar::encrypt(const char* text)
{
    return text;
}

const char* Caesar::decrypt(const char* text)
{
    std::string* decryptedText = new std::string{};
    int size = 0;
    while (text[size] != '\0')
    {
        decryptedText->push_back(text[size] - 'A' - m_K1 % 26  + 'A');
        ++size;
    }

    return decryptedText->c_str();
}
