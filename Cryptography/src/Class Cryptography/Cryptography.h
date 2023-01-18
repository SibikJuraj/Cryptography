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
	void setCurrentCipher(int&& cipher);
	const int& getCurrentCipher();
	void addCipher(std::unique_ptr<ICipherPanelFactory>& factory, std::vector<const char*>& cipherNames, std::unique_ptr<ICipherPanel>&& panel);
	GUI& getGUI() const;
private:
	Cryptography(IGUIFactory& factory);

	std::unique_ptr<GUI> m_GUI;
	int m_CurrentCipher;
};