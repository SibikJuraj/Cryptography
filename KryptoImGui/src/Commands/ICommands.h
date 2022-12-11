#pragma once

#include <memory>
#include <vector>
#include <Text/TextLoader.h>

class GUI;
class Panel;

class ICommand
{
public:
	virtual void execute() = 0;
	virtual std::shared_ptr<ICommand> clone() const = 0 ;
};

class CommandNull : public ICommand
{
public:
	CommandNull() = default;
	~CommandNull() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandNull>(*this);
	}
	virtual void execute() override
	{
	}
};

class CommandContainer : public ICommand
{
public:
	CommandContainer() : m_Elements{ std::vector<std::shared_ptr<ICommand>>() } {}
	~CommandContainer() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandContainer>(*this);
	}

	virtual void execute() override
	{
		for (int i{ 0 }; i < m_Elements.size(); ++i)
			m_Elements[i]->execute();
	}

	void addElement(std::shared_ptr<ICommand>&& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	void clear()
	{
		m_Elements.clear();
	}
private:
	std::vector<std::shared_ptr<ICommand>> m_Elements;
};

class CommandCipherSettings : public ICommand
{
public:
	CommandCipherSettings(Panel& panel) : m_Panel{ panel } {}
	~CommandCipherSettings() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{ 
		return std::make_shared<CommandCipherSettings>(*this);
	}
	virtual void execute() override;
private:
	Panel& m_Panel;
};

class CommandUpdateText : public ICommand
{
public:
	CommandUpdateText() = default;
	~CommandUpdateText() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandUpdateText>(*this);
	}
	virtual void execute() override;
};

class CommandCipherDecrypt : public ICommand
{
public:
	CommandCipherDecrypt() = default;
	~CommandCipherDecrypt() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandCipherDecrypt>(*this);
	}
	virtual void execute() override;
};

class CommandCipherEncrypt : public ICommand
{
public:
	CommandCipherEncrypt() = default;
	~CommandCipherEncrypt() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandCipherEncrypt>(*this);
	}
	virtual void execute() override;
};

class CommandOpenLoadWindow : public ICommand
{
public:
	CommandOpenLoadWindow(GUI&& gui) : m_GUI{ gui } {}
	~CommandOpenLoadWindow() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandOpenLoadWindow>(*this);
	}
	virtual void execute() override;
private:
	GUI& m_GUI;
};

class CommandOpenSaveWindow : public ICommand
{
public:
	CommandOpenSaveWindow(GUI& gui) : m_GUI{ gui } {}
	~CommandOpenSaveWindow() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandOpenSaveWindow>(*this);
	}
	virtual void execute() override;
private:
	GUI& m_GUI;
};
