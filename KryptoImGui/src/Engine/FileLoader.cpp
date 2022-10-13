#include "FileLoader.h"
#include <fstream>
#include <sstream>

FileLoader::FileLoader()
    : m_File{loadFile()->c_str()}
{
}

FileLoader::~FileLoader()
{
    delete m_File;
    m_File = nullptr;
}

const char* FileLoader::getFile()
{
    return m_File;
}

std::string* FileLoader::loadFile()
{
    try
    {
        std::ostringstream sstream;
        std::fstream fs("texts/text.txt");
        sstream << fs.rdbuf();
        std::string* str = new std::string(sstream.str());
        return str;
    }
    catch (...)
    {
        return nullptr;
    }
}
