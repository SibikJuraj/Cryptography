#pragma once

#include <vector>
#include <memory>

#include "Engine/Commands/ICommand.h"
#include "GUIElements.h"

class IGUIFactory
{
public:
	virtual std::unique_ptr<Panel> createPanel(const char* label) = 0;
	virtual std::unique_ptr<Button> createButton(const char* label, ICommand* command) = 0;
	virtual std::unique_ptr<Combobox> createCombobox(const char* label, const std::vector<const char*>& items, ICommand* command) = 0;
	virtual std::unique_ptr<Checkbox> createCheckbox(const char* label, bool& value) = 0;
	virtual std::unique_ptr<Textbox> createTextbox(const char* text) = 0;
	virtual std::unique_ptr<Plot> createPlot(const char* label, const char* data, int count) = 0;
};