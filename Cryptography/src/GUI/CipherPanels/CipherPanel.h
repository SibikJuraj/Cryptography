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

class CaesarPanel : public Panel
{
public:
	CaesarPanel()
		: Panel("CaesarPanel"), m_Cipher{ Caesar() }
	{}
protected:
	Caesar m_Cipher;
};

class AffinePanel : public Panel
{
public:
	AffinePanel()
		: Panel("AffinePanel"), m_Cipher{ Affine() }
	{}
protected:
	Affine m_Cipher;
};

class VigenerePanel : public Panel
{
public:
	VigenerePanel()
		: Panel("VigenerePanel"), m_Cipher{ Vigenere() }
	{}
protected:
	Vigenere m_Cipher;
};

class HillPanel : public Panel
{
public:
	HillPanel()
		: Panel("HillPanel") {}/*, m_Cipher{ Hill() }
	{}
protected:
	Hill m_Cipher;*/
};

class StreamPanel : public Panel
{
public:
	StreamPanel()
		: Panel("StreamPanel"), m_Cipher{ Stream() }
	{}
protected:
	Stream m_Cipher;
};

class RSAPanel : public Panel
{
public:
	RSAPanel()
		: Panel("RSAPanel"), m_Cipher{ RSA() }
	{}
protected:
	RSA m_Cipher;
};

class PwdAuthPanel : public Panel
{
public:
	PwdAuthPanel()
		: Panel("PwdAuthPanel"), m_Cipher{ PwdAuth() }
	{}
protected:
	PwdAuth m_Cipher;
};