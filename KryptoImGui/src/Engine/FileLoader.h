#pragma once
#include <vector>
#include <string>

class FileLoader
{
public:
	FileLoader();
	~FileLoader();
	
	std::string* loadFile();
	const char* getFile();
private:
	const char* m_File;
};