#pragma once

#include <memory>
#include <vector>
#include "Cipher.h"


class CipherManager
{
public:
	CipherManager();
	~CipherManager();

	void setCipher(int cipherID);
	void setFinetuning(bool finetuning);
	void decrypt();
	void encrypt();

	const Text& getInputText(); 
	const Text& getOutputText();
private:
	std::shared_ptr<Cipher> m_SelectedCipher;
	std::unique_ptr<Text> m_InputText;
	std::unique_ptr<Text> m_OutputText;
	std::vector<std::shared_ptr<Cipher>> m_Ciphers;
	bool m_Finetuning;
};