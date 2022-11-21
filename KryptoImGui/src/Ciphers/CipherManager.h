#pragma once

#include <memory>
#include <vector>
#include "Cipher.h"


class CipherManager
{
public:
	static CipherManager& getInstance()
	{
		static CipherManager instance;
		return instance;
	}

	~CipherManager();

	void registerCipher(Cipher* cipher);
	void setCipher(int cipherID);
	void setFinetuning(bool finetuning);
	void decrypt(Text& output);
	void encrypt(Text& output);
private:
	CipherManager();
	std::unique_ptr<Cipher> m_SelectedCipher;
	std::vector<std::unique_ptr<Cipher>> m_Ciphers;
	bool m_Finetuning;
};