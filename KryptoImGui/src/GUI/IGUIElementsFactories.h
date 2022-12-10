#pragma once

#include <vector>
#include <memory>

#include "Commands/ICommands.h"

#include "GUIElements.h"
class IGUIElementsFactory
{
public:
	virtual std::unique_ptr<Panel> createPanel(const char* label) = 0;
	virtual std::unique_ptr<Button> createButton(const char* label, const ICommand& command) = 0;
	virtual std::unique_ptr<Combobox> createCombobox(const char* label, const std::vector<const char*>& items) = 0;
	virtual std::unique_ptr<Checkbox> createCheckbox(const char* label, bool& value) = 0;
	virtual std::unique_ptr<Textbox> createTextbox(const char* label, std::string& text) = 0;
	virtual std::unique_ptr<Plot> createPlot(const char* label, const char* data, int count) = 0;
};


/// <summary>
/// ImGUI Elements Factory
/// </summary>
#include "ImGUI/ImGUIElements.h"
class ImGUIElementsFactory : public IGUIElementsFactory
{
public:
	virtual std::unique_ptr<Panel> createPanel(const char* label) override
	{
		return std::make_unique<ImGUIPanel>(label);
	}

	virtual std::unique_ptr<Button> createButton(const char* label, const ICommand& command) override
	{
		return std::make_unique<ImGUIButton>(label, command);
	}

	virtual std::unique_ptr<Combobox> createCombobox(const char* label, const std::vector<const char*>& items) override
	{
		return std::make_unique<ImGUIComboboxCipher>(label, items);
	}

	virtual std::unique_ptr<Checkbox> createCheckbox(const char* label, bool& value) override
	{
		return std::make_unique<ImGUICheckbox>(label, value);
	}

	virtual std::unique_ptr<Textbox> createTextbox(const char* label, std::string& text) override
	{
		return std::make_unique<ImGUITextbox>(label, text);
	}

	virtual std::unique_ptr<Plot> createPlot(const char* label, const char* data, int count) override
	{
		return std::make_unique<ImGUIPlotAnalysis>(label, data, count);
	}
};