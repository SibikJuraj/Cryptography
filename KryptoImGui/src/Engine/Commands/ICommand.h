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
	CommandCipherCreate(CipherManager& cipherManager, int cipherID) 
		: m_CipherManager{ cipherManager }, m_CipherID{ cipherID } {}
	~CommandCipherCreate() {}
	virtual void execute() override
	{
		m_CipherManager.setCipher(m_CipherID);
	}
private:
	int m_CipherID;
	CipherManager& m_CipherManager;
};

class CommandCipherDecrypt : public ICommand
{
public:
	CommandCipherDecrypt(CipherManager& cipherManager)
		: m_CipherManager{ cipherManager } {}
	~CommandCipherDecrypt() {}
	virtual void execute() override
	{
		m_CipherManager.decrypt();
	}
private:
	CipherManager& m_CipherManager;
};

class CommandCipherEncrypt : public ICommand
{
public:
	CommandCipherEncrypt(CipherManager& cipherManager)
		: m_CipherManager{ cipherManager } {}
	~CommandCipherEncrypt() {}
	virtual void execute() override
	{
		m_CipherManager.encrypt();
	}
private:
	CipherManager& m_CipherManager;
};