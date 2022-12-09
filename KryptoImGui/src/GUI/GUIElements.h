#pragma once

#include <vector>
#include <memory>
#include "Commands/ICommand.h"

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
	~Panel() = default;

	void addElement(const IGUIElement& element) 
	{
		//m_Elements.push_back(nullptr);
	}
protected:
	const char* m_Label;
	std::vector<std::unique_ptr<IGUIElement>> m_Elements;
};

class Button : public IGUIElement
{
public:
	Button(const char* label, const ICommand& command)
		: m_Label{ label }, m_Command{ command.clone() }
	{}
	~Button() = default;
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
	~Combobox() = default;
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
	~Checkbox() = default;
protected:
	const char* m_Label;
	bool& m_Value;
};

class Textbox : public IGUIElement
{
public:
	Textbox(const char* text, const ICommand& command)
		: m_Text{ text }, m_Command{ command.clone() }
	{}
	~Textbox() = default;
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
	~Plot() = default;
protected:
	const char* m_Label;
	const char* m_Data;
	int m_Count;
};