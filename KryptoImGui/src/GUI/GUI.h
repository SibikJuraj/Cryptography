#pragma once

#include <vector>
#include "GUIElements.h"

class GUI
{
public:
	GUI(int width, int height) : m_Width{ width }, m_Height{ height },
		m_Elements{ std::vector< std::unique_ptr<IGUIElement>>() } {}
	~GUI() = default;

	virtual void render() = 0;
	virtual bool isRunning() = 0;
	virtual void addElement(std::unique_ptr<IGUIElement> element) = 0;
protected:
	std::vector<std::unique_ptr<IGUIElement>> m_Elements;
	int m_Width;
	int m_Height;
};