#pragma once
#include <memory>
#include "GUI.h"

class IGUIFactory
{
public:
	virtual std::unique_ptr<GUI> createGUI(int width, int height) = 0;
};

/// <summary>
/// ImGUI Factory
/// </summary>
#include "ImGUI/ImGUI.h"
class ImGUIFactory : public IGUIFactory
{
public:
	virtual std::unique_ptr<GUI> createGUI(int width, int height) override
	{
		return std::make_unique<ImGUI>(width, height);
	}
};