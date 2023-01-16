#pragma once

#include <memory>
#include "GUI/GUIFactories.h"

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

	void setInputText(std::string&& text);
	const std::string& getInputText();
	void setOutputText(std::string&& text);
	const std::string& getOutputText();

	void setCurrentCipher(int&& cipher);
	const int& getCurrentCipher();
	void addCipher(std::unique_ptr<CipherPanelFactory>& factory, std::vector<const char*>& cipherNames, std::unique_ptr<CipherPanel>&& panel);

	GUI& getGUI() const;
private:
	Cryptography(IGUIFactory& factory);

	std::unique_ptr<GUI> m_GUI;
	std::unique_ptr<std::string> m_InputText;
	std::unique_ptr<std::string> m_OutputText;
	int m_CurrentCipher;
};