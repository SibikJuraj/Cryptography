#pragma once
#include <string>
#include <string_view>
#include <vector>

#include "Alphabet.h"

class Text
{
public:
	Text(int alphabetLength);
	Text(std::string_view pathToAlphabet);
	Text(const Text& other);
	bool loadText(std::string_view path);
	Alphabet loadAlphabet(int alphabetLength);
	Alphabet loadAlphabet(std::string_view path);
	bool saveText(std::string_view path);
	void removeSpaces();
	void sliceText(std::vector<std::string>& parts);
	std::string& getText();
	Alphabet& getAlphabet();
private:
	Alphabet m_Alphabet;
	std::string m_Text;
};