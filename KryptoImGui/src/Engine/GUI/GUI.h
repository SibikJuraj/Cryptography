#pragma once

#include <vector>
#include "Text/Text.h"
#include "GUIElements.h"

class GUI
{
public:
	GUI() : m_Elements{ std::vector<IGUIElement>() } {}
	~GUI() = default;

	virtual void preRun() = 0;
	virtual void run(std::vector<const char*> items, const char* curItem,
		int& selectedCipher, Text& iText, Text& oText, bool& fineTuning, bool& enLanguage) = 0;
	virtual void postRun() = 0;
	virtual bool isRunning() = 0;

	std::vector<IGUIElement> m_Elements;

};