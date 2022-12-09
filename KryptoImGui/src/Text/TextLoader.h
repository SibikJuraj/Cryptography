#pragma once

#include <memory>
#include <string_view>
#include <fstream>
#include <sstream>

#include <io.h>
#include <fcntl.h>

namespace TextLoader
{
    inline std::string loadText(const std::string_view&& path)
	{
        std::ifstream fs(path.data(), std::ios_base::binary);

        fs.seekg(0, std::ios::end);
        fs.seekg(0, std::ios::beg);
        std::string text{ };
        text.assign((std::istreambuf_iterator<char>(fs)),
            std::istreambuf_iterator<char>());

        return text;
	}

    inline void saveText(const std::string_view&& path, const std::string_view text, bool append = false)
    {
        std::ofstream outfile;
        if (append)
            outfile.open(path.data(), std::ios_base::app);
        else
            outfile.open(path.data());
        outfile << text;
    }
}