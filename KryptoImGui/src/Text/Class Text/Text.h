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
	Text(std::unique_ptr<std::string> text, std::unique_ptr<std::vector<int>> spaces,
		std::unique_ptr<AnalysisOfText> analysis);
	Text(const Text& other);
	std::string textWithSpaces();

	std::string& getText();
	const std::string& getText() const;
	AnalysisOfText& getTextAnalysis();
	const AnalysisOfText& getTextAnalysis() const;
private:
	std::unique_ptr<AnalysisOfText> m_AnalysisOfText;
	std::unique_ptr<std::string> m_Text;
	std::unique_ptr<std::vector<int>> m_Spaces;
};