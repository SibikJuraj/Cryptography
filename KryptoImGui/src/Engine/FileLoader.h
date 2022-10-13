#pragma once
#include <vector>
#include <string_view>

class FileLoader
{
public:
	FileLoader();
	~FileLoader();
	
	std::string_view getFile();
private:
	std::string m_File;
};