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
	virtual std::unique_ptr<Combobox> createCombobox(const char* label, const std::vector<const char*>& items, int& selected, const ICommand& command = CommandNull()) = 0;
	virtual std::unique_ptr<Checkbox> createCheckbox(const char* label, bool& value) = 0;
	virtual std::unique_ptr<Textbox> createTextbox(const char* label, std::string& text) = 0;
	virtual std::unique_ptr<InputInt> createInputInt(const char* label, int& value, const ICommand& command = CommandNull(), const std::pair<int, int> range = { INT_MIN, INT_MAX }) = 0;
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

	virtual std::unique_ptr<Combobox> createCombobox(const char* label, const std::vector<const char*>& items, int& selected, const ICommand& command) override
	{
		return std::make_unique<ImGUICombobox>(label, items, selected, command);
	}

	virtual std::unique_ptr<Checkbox> createCheckbox(const char* label, bool& value) override
	{
		return std::make_unique<ImGUICheckbox>(label, value);
	}

	virtual std::unique_ptr<Textbox> createTextbox(const char* label, std::string& text) override
	{
		return std::make_unique<ImGUITextbox>(label, text);
	}

	virtual std::unique_ptr<InputInt> createInputInt(const char* label, int& value, const ICommand& command, const std::pair<int, int> range) override
	{
		return std::make_unique<ImGUIInputInt>(label, value, command, range);
	}

	virtual std::unique_ptr<Plot> createPlot(const char* label, const char* data, int count) override
	{
		return std::make_unique<ImGUIPlotAnalysis>(label, data, count);
	}
};