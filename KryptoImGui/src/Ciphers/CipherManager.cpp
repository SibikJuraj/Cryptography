#include "CipherManager.h"

CipherManager::CipherManager() 
	: m_Finetuning{ false }, m_Ciphers{ std::vector<std::unique_ptr<Cipher>>() }, m_SelectedCipher{nullptr}
{
}

CipherManager::~CipherManager()
{
}

void CipherManager::registerCipher(Cipher* cipher)
{
	m_Ciphers.emplace_back(cipher);
}

void CipherManager::setCipher(int cipherID)
{
	m_SelectedCipher.reset(m_Ciphers[cipherID].get());
}

void CipherManager::setFinetuning(bool finetuning)
{
	m_Finetuning = finetuning;
}

void CipherManager::decrypt(Text& output)
{ 
	m_SelectedCipher->decrypt(output, m_Finetuning);
}

void CipherManager::encrypt(Text& output)
{
	m_SelectedCipher->encrypt(output, m_Finetuning);
}
