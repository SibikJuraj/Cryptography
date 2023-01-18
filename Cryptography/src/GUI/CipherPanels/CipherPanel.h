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

template <typename C, typename T>
class CipherPanel : public ICipherPanel
{
public:
	CipherPanel(const char* label, C cipher)
		: ICipherPanel(label), m_Cipher{cipher}
	{}

	virtual const char* getCipherName() override
	{
		return m_Cipher.getName();
	}
protected:
	T m_CipherInput;
	T m_CipherOutput;
	C m_Cipher;
};

class CaesarPanel : public CipherPanel<Caesar,std::string>
{
public:
	CaesarPanel()
		: CipherPanel("CaesarPanel", Caesar())
	{}
};

class AffinePanel : public CipherPanel<Affine, std::string>
{
public:
	AffinePanel()
		: CipherPanel("AffinePanel", Affine())
	{}
};

class VigenerePanel : public CipherPanel<Vigenere, std::string>
{
public:
	VigenerePanel()
		: CipherPanel("VigenerePanel", Vigenere())
	{}
};

class HillPanel : public CipherPanel<Hill, std::string>
{
public:
	HillPanel()
		: CipherPanel("HillPanel", Hill())
	{}
};

class StreamPanel : public CipherPanel<Stream, std::string>
{
public:
	StreamPanel()
		: CipherPanel("StreamPanel", Stream())
	{}
};

class RSAPanel : public CipherPanel<RSA, std::string>
{
public:
	RSAPanel()
		: CipherPanel("RSAPanel", RSA())
	{}
};

class PwdAuthPanel : public CipherPanel<PwdAuth, std::string>
{
public:
	PwdAuthPanel()
		: CipherPanel("PwdAuthPanel", PwdAuth())
	{}
};