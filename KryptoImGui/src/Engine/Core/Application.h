#pragma once

#include <memory>
#include "OpenGLWindow.h"
#include "Text/Text.h"
#include "Ciphers/Cipher.h"

#include "Text/Analysis/AnalysisOfLang.h"

class Cipher;
class AnalysisOfLang;

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

	void createCipherClass();
	const AnalysisOfLang& getLanguage() const;
	int getAlphabetLength() const;
private:
	Application();

	std::unique_ptr<OpenGLWindow> m_Window;
	std::unique_ptr<AnalysisOfLang> m_Language;
	std::unique_ptr<Text> m_Text;
	std::unique_ptr<Cipher> m_Cipher;
	int m_SelectedOption;
};