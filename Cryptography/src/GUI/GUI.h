#pragma once

#include <vector>
#include "CipherPanels/CipherPanelFactory.h"
#include "IGUIElementsFactories.h"

class GUI
{
public:
	GUI(int width, int height) : m_Width{ width }, m_Height{ height },
		m_Elements{ std::vector<std::unique_ptr<Panel>>() } {}
	~GUI() = default;

	virtual void render() = 0;
	virtual bool isRunning() = 0;
	virtual void addElement(std::unique_ptr<Panel>&& element) = 0;
	virtual std::unique_ptr<CipherPanelFactory> getCipherPanelFactory() = 0;
	virtual std::unique_ptr<IGUIElementsFactory> getElementFactory() = 0;

	virtual void openSaveWindow() = 0;
	virtual void openLoadWindow() = 0;
protected:
	std::vector<std::unique_ptr<Panel>> m_Elements;
	int m_Width;
	int m_Height;
};