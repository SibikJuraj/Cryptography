#pragma once
#include <string>
#include <string_view>
#include <vector>

#include "Alphabet.h"

const Alphabet c_SkAlphabet{ std::vector<double>{ {0.114171257},{0.01352028 },{0.030545819},{0.050075113},{0.08012018 },{0.013019529},{0.002003005},{0.020030045},{0.081622434},{0.018027041},{0.046569855},{0.030045068},{0.040560841},{0.074111167},{0.09313971 },{0.020530796},{0          },{0.04907361 },{0.053079619},{0.049574362},{0.044066099},{0.036054081},{0          },{0.000500751},{0.019529294},{0.020030045}}, 0.06027 };
const Alphabet c_EnAlphabet{ std::vector<double>{ {0.006070350},{0.000217952},{0.002229265},{0.001455578},{0.012900369},{0.000424793},{0.000292483},{0.002284821},{0.006918055},{0.000001709},{0.000032479},{0.000846167},{0.000747191},{0.004269467},{0.005109480},{0.001241045},{0.000000171},{0.004660072},{0.004740244},{0.009967846},{0.000513341},{0.000090258},{0.000101711},{0.000000513},{0.000389408},{0.000000171}}, 0.065504939 };

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
	Alphabet& getAlphabet();
	const Alphabet& getAlphabet() const;

	Alphabet& getLanguage();
	const Alphabet& getLanguage() const;
private:
	Alphabet m_Alphabet;
	std::string m_Text;
	std::vector<int> m_Spaces;

	Alphabet m_Language;
};