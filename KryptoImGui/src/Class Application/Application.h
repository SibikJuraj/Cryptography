#pragma once

#include <memory>
#include "Ciphers/Cipher.h"
#include "GUI/GUI.h"

class Application
{
public:
	static Application& getInstance()
	{
		static Application instance;
		return instance;
	}
	~Application() = default;
	void run();
private:
	Application();
	void registerCipher(Cipher& cipher);
	std::unique_ptr<GUI> m_GUI;
	std::vector<std::unique_ptr<Cipher>> m_Ciphers;
};