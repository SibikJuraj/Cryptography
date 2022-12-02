#pragma once
#include <vector>
#include <string_view>
#include <locale>
#include <stdexcept>

class AnalysisOfLang
{
public:
	AnalysisOfLang(std::vector<std::pair<int, double>> letterIC, double ic, int nOfLetters)
		: m_LetterIC{ letterIC }, m_IC{ ic }, m_NumberOfLetters{ nOfLetters }
	{}

	inline const double operator[](char letter) const { return m_LetterIC[getIndex(letter)].second; }
	inline const double getIC() const { return m_IC; }
	inline const int getAlphabetLength() const { return m_AlphabetLength; }
	inline const int getNOLetters() const { return m_NumberOfLetters; }
protected:
	const int getIndex(char letter) const 
	{ 
		if (letter >= 'a' && letter <= 'z')
			letter = toupper(letter);
		if (letter >= 'A' && letter <= 'Z')
			return letter - 65;
		return -1;
	}
	const int m_AlphabetLength = 26;

	std::vector<std::pair<int, double>> m_LetterIC;
	double m_IC;
	int m_NumberOfLetters;
};

class AnalysisOfSKLang : public AnalysisOfLang
{
public:
	AnalysisOfSKLang() : AnalysisOfLang(std::vector<std::pair<int, double>>{ {228, 0.11417}, { 27, 0.01352 }, { 61, 0.03055 }, { 100, 0.05008 }, { 160, 0.08012 }, { 26, 0.01302 }, { 4, 0.00200 }, { 40, 0.02003 }, { 163, 0.08162 }, { 36, 0.01803 }, { 93, 0.04657 }, { 60, 0.03005 }, { 81, 0.04056 }, { 148, 0.07411 }, { 186, 0.09314 }, { 41, 0.02053 }, { 0, 0.00000 }, { 98, 0.04907 }, { 106, 0.05308 }, { 99, 0.04957 }, { 88, 0.04407 }, { 72, 0.03605 }, { 0, 0.00000 }, { 1, 0.00050 }, { 39, 0.01953 }, { 40, 0.02003 }}, 0.061182957, 1997)
	{}
};

class AnalysisOfENLang : public AnalysisOfLang
{
public:
	AnalysisOfENLang() : AnalysisOfLang(std::vector<std::pair<int, double>>{ {267, 0.07805}, { 51, 0.01491 }, { 162, 0.04735 }, { 131, 0.03829 }, { 389, 0.11371 }, { 71, 0.02075 }, { 59, 0.01725 }, { 164, 0.04794 }, { 285, 0.08331 }, { 5, 0.00146 }, { 20, 0.00585 }, { 100, 0.02923 }, { 94, 0.02748 }, { 224, 0.06548 }, { 245, 0.07162 }, { 121, 0.03537 }, { 2, 0.00058 }, { 234, 0.06840 }, { 236, 0.06899 }, { 342, 0.09997 }, { 78, 0.02280 }, { 33, 0.00965 }, { 35, 0.01023 }, { 3, 0.00088 }, { 68, 0.01988 }, { 2, 0.00058 }}, 0.065504939, 3421)
	{}
};

class AnalysisOfText : public AnalysisOfLang
{
public:
	AnalysisOfText(const std::string_view text) : AnalysisOfLang(std::vector<std::pair<int, double>>(26, std::make_pair(0, 0.0)), 0.0, 0)
	{
		for (char letter : text)
		{
			addLetter(letter);
		}
		updateStatistics();
	}

	void rotateLetters()
	{
		std::rotate(m_LetterIC.begin(), m_LetterIC.begin() + 1, m_LetterIC.end());
	}
private:
	void addLetter(char letter)
	{
		auto idx{ getIndex(letter) };
		if (idx == -1)
			return;

		++m_LetterIC[idx].first;
		++m_NumberOfLetters;
	}

	/*void removeLetter(char letter)
	{
		if (m_NumberOfLetters == 0)
			return;

		auto idx{ getIndex(letter) };
		if (idx == -1 || m_LetterIC[idx].first == 0)
			return;

		--m_LetterIC[idx].first;
		--m_NumberOfLetters;
	}*/

	void updateStatistics()
	{
		m_IC = 0;
		for (int i{ 0 }; i < m_LetterIC.size(); ++i)
		{
			m_LetterIC[i].second = ((double)m_LetterIC[i].first / m_NumberOfLetters) *
				(((double)m_LetterIC[i].first - 1) / (m_NumberOfLetters - 1));
			m_IC += m_LetterIC[i].second;
		}
	}
};