#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>


#include "Text/Analysis/AnalysisOfLang.h"

class Text
{
public:
	Text();
	Text(std::string_view path);
	Text(const Text& other);
	void analyzeText();
	bool saveText(std::string_view path);
	void removeSpaces();
	std::string textWithSpaces();
	void sliceText(std::vector<Text>& parts) const;

	std::string& getText();
	const std::string& getText() const;
	AnalysisOfText& getTextAnalysis();
	const AnalysisOfText& getTextAnalysis() const;

	AnalysisOfLang& getLanguage();
	const AnalysisOfLang& getLanguage() const;
private:
	AnalysisOfText m_AnalysisOfText;
	std::unique_ptr<AnalysisOfLang> m_Language;
	std::string m_Text;
	std::vector<int> m_Spaces;
};