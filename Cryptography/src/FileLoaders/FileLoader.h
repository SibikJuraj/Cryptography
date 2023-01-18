#pragma once

template <typename T>
class FileLoader
{
public:
	virtual T loadFile(const std::string& path) = 0;
	virtual void saveFile(const std::string& path, const T& text, bool append = false) = 0;
};