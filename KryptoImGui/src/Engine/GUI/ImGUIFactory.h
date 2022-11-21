#pragma once

#include "IGUIFactory.h"
#include "ImGUIElements.h"

#include <memory>

class ImGUIFactory : public IGUIFactory
{
public:
	virtual std::unique_ptr<Panel> createPanel(const char* label) override
	{ return std::make_unique<ImGUIPanel>(label); }

	virtual std::unique_ptr<Button> createButton(const char* label, const ICommand& command) override
	{ return std::make_unique<ImGUIButton>(label, command); }

	virtual std::unique_ptr<Combobox> createCombobox(const char* label, const std::vector<const char*>& items, const ICommand& command) override
	{ return std::make_unique<ImGUICombobox>(label, items, command); }

	virtual std::unique_ptr<Checkbox> createCheckbox(const char* label, bool& value) override
	{ return std::make_unique<ImGUICheckbox>(label, value); }

	virtual std::unique_ptr<Textbox> createTextbox(const char* text) override
	{ return std::make_unique<ImGUITextbox>(text); }

	virtual std::unique_ptr<Plot> createPlot(const char* label, const char* data, int count) override
	{ return std::make_unique<ImGUIPlotAnalysis>(label, data, count); }
};