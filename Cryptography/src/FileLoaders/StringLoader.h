#pragma once

#include <memory>
#include <string_view>
#include <fstream>
#include <sstream>

#include <io.h>
#include <fcntl.h>
#include "FileLoader.h"

class StringLoader : public FileLoader<std::string>
{
public:
    virtual std::string loadFile(const std::string& path) override;
    virtual void saveFile(const std::string& path, const std::string& text, bool append = false) override;
};

inline std::string StringLoader::loadFile(const std::string& path)
{
    std::ifstream fs(path.data(), std::ios_base::binary);

    fs.seekg(0, std::ios::end);
    fs.seekg(0, std::ios::beg);
    std::string text{ };
    text.assign((std::istreambuf_iterator<char>(fs)),
        std::istreambuf_iterator<char>());

    return text;
}

inline void StringLoader::saveFile(const std::string& path, const std::string& text, bool append)
{
    std::ofstream outfile;
    if (append)
        outfile.open(path.data(), std::ios_base::app);
    else
        outfile.open(path.data());
    outfile << text;
}
