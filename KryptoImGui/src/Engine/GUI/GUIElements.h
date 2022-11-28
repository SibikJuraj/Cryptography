#pragma once

#include <vector>
#include <memory>
#include "Engine/Commands/ICommand.h"

class IGUIElement
{
public:
	virtual void draw() = 0;
};

class Panel : public IGUIElement
{
public:
	Panel(const char* label) : m_Label{label}, m_Elements{ std::vector<std::unique_ptr<IGUIElement>>()}
	{}
	~Panel() { delete m_Label;  m_Label = nullptr; }

	void addElement(const IGUIElement& element) { m_Elements.emplace_back(element); }
protected:
	const char* m_Label;
	std::vector<std::unique_ptr<IGUIElement>> m_Elements;
};

class Button : public IGUIElement
{
public:
	Button(const char* label, const ICommand& command)
		: m_Label{ label }, m_Command{ std::make_unique<ICommand>(command) }
	{}
	~Button() { delete m_Label;  m_Label = nullptr; }
protected:
	const char* m_Label;
	std::unique_ptr<ICommand> m_Command;
};

class Combobox : public IGUIElement
{
public:
	Combobox(const char* label, const std::vector<const char*>& items)
		: m_Label{ label }, m_Items{ items }, m_SelectedValue{ 0 }
	{}
	~Combobox() { delete m_Label;  m_Label = nullptr; }
protected:
	const char* m_Label;
	const std::vector<const char*> m_Items;
	int m_SelectedValue;
};

class Checkbox : public IGUIElement
{
public:
	Checkbox(const char* label, bool& value)
		: m_Label{ label }, m_Value{ value }
	{}
	~Checkbox() { delete m_Label;  m_Label = nullptr; }
protected:
	const char* m_Label;
	bool& m_Value;
};

class Textbox : public IGUIElement
{
public:
	Textbox(const char* text, const ICommand* command)
		: m_Text{ text }, m_Command{ std::make_unique<ICommand>(command) }
	{}
	~Textbox() { delete m_Text;  m_Text = nullptr; }
protected:
	const char* m_Text;
	std::unique_ptr<ICommand> m_Command;
};

class Plot : public IGUIElement
{
public:
	Plot(const char* label, const char* data, int count)
		: m_Label{ label }, m_Data { data }, m_Count{ count }
	{}
	~Plot() { delete m_Label; m_Label = nullptr; delete m_Data; m_Data = nullptr; }
protected:
	const char* m_Label;
	const char* m_Data;
	int m_Count;
};