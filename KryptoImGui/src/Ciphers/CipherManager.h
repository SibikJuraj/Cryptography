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
	void decrypt();
	void encrypt();

	const Text& getInputText(); 
	const Text& getOutputText();
private:
	CipherManager();
	std::unique_ptr<Cipher> m_SelectedCipher;
	std::shared_ptr<Text> m_InputText;
	std::shared_ptr<Text> m_OutputText;
	std::vector<std::unique_ptr<Cipher>> m_Ciphers;
	bool m_Finetuning;
};