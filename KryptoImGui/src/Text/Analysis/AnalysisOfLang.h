#pragma once
#include <vector>
#include <string_view>
#include <stdexcept>

class AnalysisOfLang
{
public:
	AnalysisOfLang(std::vector<double> letterIC, double ic)
		: m_LetterIC{letterIC}, m_IC{ic}
	{}

	const double operator[](char letter) const
	{ 
		if (letter < 'A' || letter > 'Z') {
			throw std::invalid_argument("received invalid letter");
		}

		return m_LetterIC[letter - 65];
	}

	const double getIC() const { return m_IC; }
	const int getAlphabetLength() const { return m_AlphabetLength; }
protected:
	std::vector<double> m_LetterIC;
	double m_IC;
	const int m_AlphabetLength = 26;
};

class AnalysisOfSKLang : public AnalysisOfLang
{
public:
	AnalysisOfSKLang() : AnalysisOfLang(std::vector<double>{ {0.114171257}, { 0.01352028 }, { 0.030545819 }, { 0.050075113 }, { 0.08012018 }, { 0.013019529 }, { 0.002003005 }, { 0.020030045 }, { 0.081622434 }, { 0.018027041 }, { 0.046569855 }, { 0.030045068 }, { 0.040560841 }, { 0.074111167 }, { 0.09313971 }, { 0.020530796 }, { 0 }, { 0.04907361 }, { 0.053079619 }, { 0.049574362 }, { 0.044066099 }, { 0.036054081 }, { 0 }, { 0.000500751 }, { 0.019529294 }, { 0.020030045 }}, 0.061182957)
	{}
};

class AnalysisOfENLang : public AnalysisOfLang
{
public:
	AnalysisOfENLang() : AnalysisOfLang(std::vector<double>{ {0.078047355}, { 0.014907922 }, { 0.047354575 }, { 0.038292897 }, { 0.113709442 }, { 0.020754165 }, { 0.017246419 }, { 0.047939199 }, { 0.083308974 }, { 0.001461561 }, { 0.005846244 }, { 0.029231219 }, { 0.027477346 }, { 0.06547793 }, { 0.071616486 }, { 0.035369775 }, { 0.000584624 }, { 0.068401052 }, { 0.068985677 }, { 0.099970769 }, { 0.022800351 }, { 0.009646302 }, { 0.010230927 }, { 0.000876937 }, { 0.019877229 }, { 0.000584624 }}, 0.065504939)
	{}
};

class AnalysisOfText : public AnalysisOfLang
{
public:
	AnalysisOfText() : AnalysisOfLang(std::vector<double>(26, 0.0), 0.0)
	{}

	double& getIC() { return m_IC; }
	std::vector<double>& getLetters() { return m_LetterIC; }

	double& operator[](char letter)
	{
		if (letter >= 'A' && letter <= 'Z') 
		{
			return m_LetterIC[letter - 65];
		}
		throw std::invalid_argument("received invalid letter");
	}
};