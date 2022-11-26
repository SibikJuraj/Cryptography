#include "CipherManager.h"

CipherManager::CipherManager()
	: m_Finetuning{ false }, m_Ciphers{ std::vector<std::unique_ptr<Cipher>>() }, m_SelectedCipher{nullptr},
	 m_InputText{ std::make_unique<Text>("texts/vigenere/text4_enc.txt")}
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

void CipherManager::decrypt()
{ 
	*m_OutputText = m_SelectedCipher->decrypt(*m_InputText, m_Finetuning);
}

void CipherManager::encrypt()
{
	*m_OutputText = m_SelectedCipher->encrypt(*m_InputText, m_Finetuning);
}

const Text& CipherManager::getInputText()
{
	return *m_InputText;
}

const Text& CipherManager::getOutputText()
{
	return *m_OutputText;
}