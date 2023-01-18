#pragma once

#include "Ciphers/Cipher.h"
#include "Ciphers/Caesar.h"
#include "Ciphers/Affine.h"
#include "Ciphers/Vigenere.h"
#include "Ciphers/Hill.h"
#include "Ciphers/Stream.h"
#include "Ciphers/RSA.h"
#include "Ciphers/PwdAuth.h"

#include "GUI/GUIElements.h"

class ICipherPanel : public Panel
{
public:
	ICipherPanel(const char* label)
		: Panel(label)
	{}
	virtual const char* getCipherName() = 0;
};

template <typename K, typename T>
class CipherPanel : public ICipherPanel
{
public:
	CipherPanel(const char* label, Cipher<K, T>* cipher)
		: ICipherPanel(label), m_Cipher{cipher}
	{}
	~CipherPanel()
	{
		delete m_Cipher;
		m_Cipher = nullptr;
	}

	virtual const char* getCipherName() override
	{
		return m_Cipher->getName();
	}
protected:
	T m_CipherInput;
	T m_CipherOutput;
	Cipher<K, T>* m_Cipher;
};

class CaesarPanel : public CipherPanel<CaesarKey,std::string>
{
public:
	CaesarPanel()
		: CipherPanel("CaesarPanel", new Caesar())
	{}
};

class AffinePanel : public CipherPanel<AffineKey, std::string>
{
public:
	AffinePanel()
		: CipherPanel("AffinePanel", new Affine())
	{}
};

class VigenerePanel : public CipherPanel<VigenereKey, std::string>
{
public:
	VigenerePanel()
		: CipherPanel("VigenerePanel", new Vigenere())
	{}
};

class HillPanel : public CipherPanel<HillKey, std::string>
{
public:
	HillPanel()
		: CipherPanel("HillPanel", new Hill())
	{}
};

class StreamPanel : public CipherPanel<StreamKey, std::string>
{
public:
	StreamPanel()
		: CipherPanel("StreamPanel", new Stream())
	{}
};

class RSAPanel : public CipherPanel<RSAKey, std::string>
{
public:
	RSAPanel()
		: CipherPanel("RSAPanel", new RSA())
	{}
};

class PwdAuthPanel : public CipherPanel<PwdAuthKey, std::string>
{
public:
	PwdAuthPanel()
		: CipherPanel("PwdAuthPanel", new PwdAuth())
	{}
};