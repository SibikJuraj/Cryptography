#include "CipherManager.h"
#include "Ciphers/Caesar.h"
#include "Ciphers/Affine.h"
#include "Ciphers/Viegener.h"

CipherManager::CipherManager()
	: m_Finetuning{ false }, m_Ciphers{ std::vector<std::shared_ptr<Cipher>>() },
	 m_InputText{ std::make_unique<Text>("texts/vigenere/text4_enc.txt")}, m_OutputText{nullptr}
{
	m_Ciphers.push_back(std::make_shared<Caesar>());
	m_Ciphers.push_back(std::make_shared<Affine>());
	m_Ciphers.push_back(std::make_shared<Viegener>());
	m_SelectedCipher = m_Ciphers[0];
}

CipherManager::~CipherManager()
{
}

void CipherManager::setCipher(int cipherID)
{
	m_SelectedCipher = m_Ciphers[cipherID];
}

void CipherManager::setFinetuning(bool finetuning)
{
	m_Finetuning = finetuning;
}

void CipherManager::decrypt()
{ 
	m_OutputText.reset(&m_SelectedCipher->decrypt(*m_InputText, m_Finetuning));
}

void CipherManager::encrypt()
{
	m_OutputText.reset(&m_SelectedCipher->encrypt(*m_InputText, m_Finetuning));
}

const Text& CipherManager::getInputText()
{
	return *m_InputText;
}

const Text& CipherManager::getOutputText()
{
	return *m_OutputText;
}