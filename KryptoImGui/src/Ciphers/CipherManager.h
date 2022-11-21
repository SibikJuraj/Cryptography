#pragma once

#include <vector>
#include <memory>
#include "Cipher.h"

class CipherManager
{
public:
	static CipherManager& getInstance()
	{
		static CipherManager instance;
		return instance;
	}

	~CipherManager() {}

	void registerCipher(const Cipher& cipher) { m_Ciphers.push_back(cipher); }
	void setCipher(int cipherID) 
	{ m_SelectedCipher = std::make_unique<Cipher>(m_Ciphers[cipherID]); }
	void setFinetuning(bool finetuning) { m_Finetuning = finetuning; }
	void decrypt() { /*m_SelectedCipher->decrypt();*/ }
	void encrypt() {/*m_SelectedCipher->encrypt();*/ }
private:
	CipherManager() : m_SelectedCipher{ nullptr }, m_Ciphers{ std::vector<Cipher>() } {}
	std::unique_ptr<Cipher> m_SelectedCipher;
	std::vector<Cipher> m_Ciphers;
	bool m_Finetuning;
};