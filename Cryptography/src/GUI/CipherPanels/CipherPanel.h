#pragma once
#include "Ciphers/Cipher.h"
#include "Ciphers/Caesar.h"
#include "Ciphers/Affine.h"
#include "Ciphers/Vigenere.h"
//#include "Ciphers/Hill.h"
#include "Ciphers/Stream.h"
#include "Ciphers/RSA.h"
#include "Ciphers/PwdAuth.h"

#include "GUI/GUIElements.h"


class CipherPanel : public Panel
{
public:
	CipherPanel(const char* label)
		: Panel(label)
	{}
	virtual const char* getCipherName() = 0;
};

class CaesarPanel : public CipherPanel
{
public:
	CaesarPanel()
		: CipherPanel("CaesarPanel"), m_Cipher{ Caesar() }
	{}
	virtual const char* getCipherName() override
	{
		return m_Cipher.getName();
	}
protected:
	Caesar m_Cipher;
};

class AffinePanel : public CipherPanel
{
public:
	AffinePanel()
		: CipherPanel("AffinePanel"), m_Cipher{ Affine() }
	{}
	virtual const char* getCipherName() override
	{
		return m_Cipher.getName();
	}
protected:
	Affine m_Cipher;
};

class VigenerePanel : public CipherPanel
{
public:
	VigenerePanel()
		: CipherPanel("VigenerePanel"), m_Cipher{ Vigenere() }
	{}
	virtual const char* getCipherName() override
	{
		return m_Cipher.getName();
	}
protected:
	Vigenere m_Cipher;
};

class HillPanel : public CipherPanel
{
public:
	HillPanel()
		: CipherPanel("HillPanel"), m_Cipher{ Caesar() }
	{}
		virtual const char* getCipherName() override
	{
		return m_Cipher.getName();
	}
protected:
	Caesar m_Cipher;
};

class StreamPanel : public CipherPanel
{
public:
	StreamPanel()
		: CipherPanel("StreamPanel"), m_Cipher{ Stream() }
	{}
	virtual const char* getCipherName() override
	{
		return m_Cipher.getName();
	}
protected:
	Stream m_Cipher;
};

class RSAPanel : public CipherPanel
{
public:
	RSAPanel()
		: CipherPanel("RSAPanel"), m_Cipher{ RSA() }
	{}
	virtual const char* getCipherName() override
	{
		return m_Cipher.getName();
	}
protected:
	RSA m_Cipher;
};

class PwdAuthPanel : public CipherPanel
{
public:
	PwdAuthPanel()
		: CipherPanel("PwdAuthPanel"), m_Cipher{ PwdAuth() }
	{}
	virtual const char* getCipherName() override
	{
		return m_Cipher.getName();
	}
protected:
	PwdAuth m_Cipher;
};