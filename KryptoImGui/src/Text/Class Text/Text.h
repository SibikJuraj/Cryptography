#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <Text/AnalysisOfLang.h>

class Text
{
public:
	Text();
	Text(std::string text, AnalysisOfText analysis);
	Text(const Text& other);

	const std::string& getText() const;
	const AnalysisOfText& getTextAnalysis() const;
	void addLetter(char letter);
	void removeLetter();
private:
	void createRawText();

	AnalysisOfText m_AnalysisOfText;
	std::string m_Text;
	std::string m_RawText;
};