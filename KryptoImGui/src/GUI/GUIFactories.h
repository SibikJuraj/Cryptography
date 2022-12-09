#pragma once
#include <memory>
#include "GUI.h"

class IGUIFactory
{
public:
	virtual std::unique_ptr<GUI> createGUI(int width, int height) = 0;
};


#include "ImGUI/ImGUI.h"
/// <summary>
/// ImGUI Factory
/// </summary>
class ImGUIFactory : public IGUIFactory
{
public:
	virtual std::unique_ptr<GUI> createGUI(int width, int height) override
	{
		return std::make_unique<ImGUI>(width, height);
	}
};