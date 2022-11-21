#pragma once

#include "Ciphers/CipherManager.h"

class ICommand
{
public:
	virtual void execute() = 0;
};

class CommandCipherCreate : public ICommand
{
public:
	CommandCipherCreate(int cipherID) : m_CipherID{ cipherID } {}
	~CommandCipherCreate() {}
	virtual void execute() override
	{
		CipherManager::getInstance().setCipher(m_CipherID);
	}
private:
	int m_CipherID;
};

class CommandCipherDecrypt : public ICommand
{
public:
	CommandCipherDecrypt(int cipherID) : m_CipherID{ cipherID } {}
	~CommandCipherDecrypt() {}
	virtual void execute() override
	{
		CipherManager::getInstance().decrypt();
	}
private:
	int m_CipherID;
};

class CommandCipherEncrypt : public ICommand
{
public:
	CommandCipherEncrypt(int cipherID) : m_CipherID{ cipherID } {}
	~CommandCipherEncrypt() {}
	virtual void execute() override
	{
		CipherManager::getInstance().encrypt();
	}
private:
	int m_CipherID;
};