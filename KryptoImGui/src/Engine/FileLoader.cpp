#include "FileLoader.h"
#include <fstream>
#include <sstream>

FileLoader::FileLoader()
{
    try
    {
        std::ifstream fs("texts/text.txt");

        fs.seekg(0, std::ios::end);
        m_File.reserve(fs.tellg());
        fs.seekg(0, std::ios::beg);
        m_File.assign((std::istreambuf_iterator<char>(fs)),
            std::istreambuf_iterator<char>());
    }
    catch (...)
    {
    }
}

FileLoader::~FileLoader()
{
}

std::string_view FileLoader::getFile()
{
    return m_File;
}
