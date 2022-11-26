#pragma once

#include "Ciphers/CipherManager.h"

class CipherManager;

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
	CommandCipherDecrypt() {}
	~CommandCipherDecrypt() {}
	virtual void execute() override
	{
		CipherManager::getInstance().decrypt();
	}
};

class CommandCipherEncrypt : public ICommand
{
public:
	CommandCipherEncrypt() {}
	~CommandCipherEncrypt() {}
	virtual void execute() override
	{
		CipherManager::getInstance().encrypt();
	}
};