#pragma once

#include <memory>
#include <vector>

#include <ImGuiFileDialog.h>
class Panel;

template <typename K, typename T>
class Cipher;

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

class CommandAddInputInt : public ICommand
{
public:
	CommandAddInputInt(std::vector<int>& val)
		: m_Value{ val }
	{}
	~CommandAddInputInt() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandAddInputInt>(*this);
	}
	virtual void execute() override
	{
		m_Value.push_back(0);
	}
private:
	std::vector<int>& m_Value;
};

class CommandRemoveInputInt : public ICommand
{
public:
	CommandRemoveInputInt(std::vector<int>& val)
		: m_Value{ val }
	{}
	~CommandRemoveInputInt() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandRemoveInputInt>(*this);
	}
	virtual void execute() override
	{
		if (m_Value.size() > 1)
			m_Value.pop_back();
	}
private:
	std::vector<int>& m_Value;
};

template <typename K, typename T>
class CommandCipherTryFindKey : public ICommand
{
public:
	CommandCipherTryFindKey(Cipher<K, T>& cipher, T& input)
		: m_Cipher{ cipher }, m_Input{ input }
	{}
	~CommandCipherTryFindKey() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandCipherTryFindKey>(*this);
	}
	virtual void execute() override
	{
		m_Cipher.tryFindKey(m_Input);
	}
private:
	Cipher<K, T>& m_Cipher;
	T& m_Input;
};

template <typename K, typename T>
class CommandUpdateText : public ICommand
{
public:
	CommandUpdateText(Cipher<K, T>& cipher, T& input, T& output)
		: m_Cipher{ cipher }, m_Input{ input }, m_Output{ output }
	{}
	~CommandUpdateText() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandUpdateText>(*this);
	}
	virtual void execute() override
	{
		m_Output = m_Cipher.update(m_Input);
	}
private:
	Cipher<K, T>& m_Cipher;
	T& m_Input;
	T& m_Output;
};

template <typename K, typename T>
class CommandCipherDecrypt : public ICommand
{
public:
	CommandCipherDecrypt(Cipher<K, T>& cipher, T& input, T& output)
		: m_Cipher{ cipher }, m_Input{ input }, m_Output{ output }
	{}
	~CommandCipherDecrypt() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandCipherDecrypt>(*this);
	}
	virtual void execute() override
	{
		m_Output = m_Cipher.decrypt(m_Input);
	}
private:
	Cipher<K, T>& m_Cipher;
	T& m_Input;
	T& m_Output;
};

template <typename K, typename T>
class CommandCipherEncrypt : public ICommand
{
public:
	CommandCipherEncrypt(Cipher<K, T>& cipher, T& input, T& output)
		: m_Cipher{ cipher }, m_Input{ input }, m_Output{ output }
	{}
	~CommandCipherEncrypt() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandCipherEncrypt>(*this);
	}
	virtual void execute() override
	{
		m_Output = m_Cipher.encrypt(m_Input);
	}
private:
	Cipher<K, T>& m_Cipher;
	T& m_Input;
	T& m_Output;
};


class CommandOpenLoadWindow : public ICommand
{
public:
	CommandOpenLoadWindow()
	{}
	~CommandOpenLoadWindow() = default;

};

class CommandOpenSaveWindow : public ICommand
{
public:
	CommandOpenSaveWindow()
	{}
	~CommandOpenSaveWindow() = default;


};

class CommandOpenImGUISaveWindow : public CommandOpenSaveWindow
{
public:
	CommandOpenImGUISaveWindow()
	{}
	~CommandOpenImGUISaveWindow() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandOpenImGUISaveWindow>(*this);
	}
	virtual void execute() override
	{
		ImGuiFileDialog::Instance()->OpenDialog("SaveFileDlgKey", "Save File", ".txt", ".");
	}
};

class CommandOpenImGUILoadWindow : public CommandOpenLoadWindow
{
public:
	CommandOpenImGUILoadWindow()
	{}
	~CommandOpenImGUILoadWindow() = default;

	virtual std::shared_ptr<ICommand> clone() const override
	{
		return std::make_shared<CommandOpenImGUILoadWindow>(*this);
	}
	virtual void execute() override
	{
		ImGuiFileDialog::Instance()->OpenDialog("LoadFileDlgKey", "Load File", ".txt", ".");
	}
};