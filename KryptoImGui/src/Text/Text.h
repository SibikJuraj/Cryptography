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
	void sliceText(std::vector<Text>& parts) const;

	std::string& getText();
	const std::string& getText() const;
	Alphabet& getAlphabet();
	const Alphabet& getAlphabet() const;
private:
	Alphabet m_Alphabet;
	std::string m_Text;

};