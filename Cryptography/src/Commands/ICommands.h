#pragma once

#include <memory>
#include <vector>

class Panel;
class ICipher;

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
	CommandCipherSettings(Panel& panel, ICipher& cipher) 
		: m_Panel{ panel } , m_Cipher{ cipher } 
	{}
	~CommandCipherSettings() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{ 
		return std::make_shared<CommandCipherSettings>(*this);
	}
	virtual void execute() override;
private:
	Panel& m_Panel;
	ICipher& m_Cipher;
};

class CommandUpdateText : public ICommand
{
public:
	CommandUpdateText(ICipher& cipher)
		: m_Cipher{ cipher }
	{}
	~CommandUpdateText() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandUpdateText>(*this);
	}
	virtual void execute() override;
private:
	ICipher& m_Cipher;
};

class CommandCipherDecrypt : public ICommand
{
public:
	CommandCipherDecrypt(ICipher& cipher) 
		: m_Cipher{ cipher } 
	{}
	~CommandCipherDecrypt() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandCipherDecrypt>(*this);
	}
	virtual void execute() override;
private:
	ICipher& m_Cipher;
};

class CommandCipherEncrypt : public ICommand
{
public:
	CommandCipherEncrypt(ICipher& cipher)
		: m_Cipher{ cipher }
	{}
	~CommandCipherEncrypt() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandCipherEncrypt>(*this);
	}
	virtual void execute() override;
private:
	ICipher& m_Cipher;
};

class CommandOpenLoadWindow : public ICommand
{
public:
	CommandOpenLoadWindow() {}
	~CommandOpenLoadWindow() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandOpenLoadWindow>(*this);
	}
	virtual void execute() override;
};

class CommandOpenSaveWindow : public ICommand
{
public:
	CommandOpenSaveWindow() {}
	~CommandOpenSaveWindow() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandOpenSaveWindow>(*this);
	}
	virtual void execute() override;
};
