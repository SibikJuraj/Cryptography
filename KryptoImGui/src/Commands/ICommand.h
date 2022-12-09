#pragma once

#include <memory>

class ICommand
{
public:
	virtual void execute() = 0;
	virtual std::unique_ptr<ICommand> clone() const = 0 ;
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
	virtual void execute() override
	{
	}
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
	virtual void execute() override
	{
	}
};