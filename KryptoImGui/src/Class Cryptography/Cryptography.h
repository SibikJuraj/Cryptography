#pragma once

#include <memory>
#include "Ciphers/Cipher.h"
#include "GUI/GUIFactories.h"
#include "GUI/IGUIElementsFactories.h"

class Cryptography
{
public:
	static Cryptography& getInstance()
	{
		static Cryptography instance{ ImGUIFactory() };
		return instance;
	}
	~Cryptography() = default;
	void run();

	Cipher& getCipher() const;

	void setInputText(std::string&& text);
	const std::string& getInputText();
	void setOutputText(std::string&& text);
	const std::string& getOutputText();

private:
	Cryptography(IGUIFactory& factory);
	void registerCipher(Cipher* cipher);

	std::unique_ptr<GUI> m_GUI;
	std::unique_ptr<std::string> m_InputText;
	std::unique_ptr<std::string> m_OutputText;
	std::vector<std::unique_ptr<Cipher>> m_Ciphers;

	int m_SelectedCipher;
};