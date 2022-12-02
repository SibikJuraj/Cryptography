#pragma once

#include <memory>
#include <string_view>
#include <fstream>
#include <sstream>

#include <io.h>
#include <fcntl.h>

namespace TextLoader
{
	std::string loadText(const std::string_view&& path)
	{
        _setmode(_fileno(stdout), _O_U8TEXT);
        _setmode(_fileno(stdin), _O_U8TEXT);

        std::ifstream fs(path.data(), std::ios_base::binary);

        fs.seekg(0, std::ios::end);
        fs.seekg(0, std::ios::beg);
        std::string text{ };
        text.assign((std::istreambuf_iterator<char>(fs)),
            std::istreambuf_iterator<char>());

        return text;
	}

    void saveText(const std::string_view&& path, const std::string_view text)
    {
        std::ofstream outfile;
        outfile.open(path.data());
        outfile << text;
    }
}