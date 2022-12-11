#pragma once

#include <memory>
#include <Text/TextLoader.h>

class GUI;


//TODO COMMANDY BY MALI BYT SHARED_PTR
class ICommand
{
public:
	virtual void execute() = 0;
	virtual std::unique_ptr<ICommand> clone() const = 0 ;
};

class CommandNull : public ICommand
{
public:
	CommandNull() = default;
	~CommandNull() = default;

	virtual std::unique_ptr<ICommand> clone() const override
	{
		return std::make_unique<CommandNull>(*this);
	}
	virtual void execute() override
	{
	}
private:
	int m_CipherID;
};


class CommandCipherCreate : public ICommand
{
public:
	CommandCipherCreate(int cipherID) : m_CipherID{ cipherID } {}
	~CommandCipherCreate() = default;

	virtual std::unique_ptr<ICommand> clone() const override
	{ 
		return std::make_unique<CommandCipherCreate>(*this);
	}
	virtual void execute() override
	{
	}
private:
	int m_CipherID;
};

class CommandCipherDecrypt : public ICommand
{
public:
	CommandCipherDecrypt() = default;
	~CommandCipherDecrypt() = default;

	virtual std::unique_ptr<ICommand> clone() const override
	{
		return std::make_unique<CommandCipherDecrypt>(*this);
	}
	virtual void execute() override;
};

class CommandCipherEncrypt : public ICommand
{
public:
	CommandCipherEncrypt() = default;
	~CommandCipherEncrypt() = default;

	virtual std::unique_ptr<ICommand> clone() const override
	{
		return std::make_unique<CommandCipherEncrypt>(*this);
	}
	virtual void execute() override;
};

class CommandOpenLoadWindow : public ICommand
{
public:
	CommandOpenLoadWindow(GUI&& gui) : m_GUI{ gui } {}
	~CommandOpenLoadWindow() = default;

	virtual std::unique_ptr<ICommand> clone() const override
	{
		return std::make_unique<CommandOpenLoadWindow>(*this);
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

	virtual std::unique_ptr<ICommand> clone() const override
	{
		return std::make_unique<CommandOpenSaveWindow>(*this);
	}
	virtual void execute() override;
private:
	GUI& m_GUI;
};
