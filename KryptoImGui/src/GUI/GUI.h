#pragma once

#include <vector>
#include "Text/Text.h"
#include "GUIElements.h"

class GUI
{
public:
	GUI() : m_Elements{ std::vector< std::unique_ptr<IGUIElement>>() } {}
	~GUI() = default;

	virtual void render() = 0;
	virtual bool isRunning() = 0;
	virtual void addElement(IGUIElement& element) = 0;
protected:
	std::vector<std::unique_ptr<IGUIElement>> m_Elements;
};