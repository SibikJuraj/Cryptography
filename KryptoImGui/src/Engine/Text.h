#pragma once
#include <string>
#include <string_view>
#include <vector>

#include "Alphabet.h"

class Text
{
public:
	Text();
	Text(std::string_view path);
	Text(const Text& other);
	void analyzeText();
	bool saveText(std::string_view path);
	void removeSpaces();
	void sliceText(std::vector<Text>& parts);

	std::string& getText();
	Alphabet& getAlphabet();
private:
	Alphabet m_Alphabet;
	std::string m_Text;

};