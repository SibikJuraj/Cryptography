#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Commands/ICommands.h"

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
	~Panel() {
		delete m_Label;
		m_Label = nullptr;
	}

	void addElement(std::unique_ptr<IGUIElement>&& element) 
	{
		m_Elements.emplace_back(std::move(element));
	}

	void clear()
	{
		m_Elements.clear();
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
	~Button() {
		delete m_Label;
		m_Label = nullptr;
	}
protected:
	const char* m_Label;
	std::shared_ptr<ICommand> m_Command;
};

class Combobox : public IGUIElement
{
public:
	Combobox(const char* label, const std::vector<const char*>& items, int& selected, const ICommand& command)
		: m_Label{ label }, m_Items{ items }, m_Selected{ selected }, m_Command{ command.clone() }
	{}
	~Combobox() {
		delete m_Label;
		m_Label = nullptr;
	}
protected:
	const char* m_Label;
	const std::vector<const char*> m_Items;
	int& m_Selected;
	std::shared_ptr<ICommand> m_Command;
};

class Checkbox : public IGUIElement
{
public:
	Checkbox(const char* label, bool& value)
		: m_Label{ label }, m_Value{ value }
	{}
	~Checkbox() {
		delete m_Label;
		m_Label = nullptr;
	}
protected:
	const char* m_Label;
	bool& m_Value;
};

class Textbox : public IGUIElement
{
public:
	Textbox(const char* label, std::string& text)
		: m_Label{ label }, m_Text{ text }
	{}
	~Textbox() {
		delete m_Label;
		m_Label = nullptr;
	}
protected:
	const char* m_Label;
	std::string& m_Text;
};


class InputInt : public IGUIElement
{
public:
	InputInt(const char* label, int& value, const ICommand& command, const std::pair<int, int> range)
		: m_Label{ label }, m_Value{ value }, m_Command{ command.clone() }, m_Range{ range }
	{}
	~InputInt() {
		delete m_Label;
		m_Label = nullptr;
	}
protected:
	const char* m_Label;
	int& m_Value;
	std::pair<int ,int> m_Range;
	std::shared_ptr<ICommand> m_Command;
};

class InputChar : public IGUIElement
{
public:
	InputChar(const char* label, char& value, const ICommand& command)
		: m_Label{ label }, m_Value{ value }, m_Command{ command.clone() }
	{}
	~InputChar() {
		delete m_Label;
		m_Label = nullptr;
	}
protected:
	const char* m_Label;
	char& m_Value;
	std::shared_ptr<ICommand> m_Command;
};

class Plot : public IGUIElement
{
public:
	Plot(const char* label, const char* data, int count)
		: m_Label{ label }, m_Data { data }, m_Count{ count }
	{}
	~Plot() {
		delete m_Label;
		m_Label = nullptr;
	}
protected:
	const char* m_Label;
	const char* m_Data;
	int m_Count;
};
