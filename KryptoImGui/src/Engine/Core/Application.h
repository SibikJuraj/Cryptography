#pragma once

#include <memory>
#include "Text/Text.h"
#include "Engine/GUI/GUI.h"

#include "Text/Analysis/AnalysisOfLang.h"

class Cipher;
class AnalysisOfLang;
class GUI;

class Application
{
public:
	static Application& getInstance()
	{
		static Application instance;
		return instance;
	}
	void run();
	~Application();

	void createCipherClass(int selectedOption);
	const AnalysisOfLang& getLanguage() const;
	void setLanguage(bool english);
	int getAlphabetLength() const;
private:
	Application();

	std::unique_ptr<GUI> m_GUI;
	std::unique_ptr<AnalysisOfLang> m_Language;
	std::unique_ptr<Text> m_Text;

	int m_CurrentCipher;
};