#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <Text/AnalysisOfLang.h>

class Text
{
public:
	static int letterCount(std::string_view text);
	void sliceText(std::vector<Text>& parts) const;

	Text();
	Text(std::string text);
	Text(std::string text, AnalysisOfText analysis);
	Text(const Text& other);

	const std::string_view& getText() const;
	const std::string_view& getRawText() const;
	const AnalysisOfText& getTextAnalysis() const;
	AnalysisOfText& getTextAnalysis();
	void addLetter(char letter);
	void addText(const std::string_view text);
	void changeLetter(char letter, int index);
	void removeLetter();
private:
	void createRawText();

	AnalysisOfText m_AnalysisOfText;
	std::string m_Text;
	std::string m_RawText;
};