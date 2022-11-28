#pragma once

#include <memory>
#include "Text/Text.h"
#include "Engine/GUI/GUI.h"
#include "Ciphers/CipherManager.h"

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
	std::unique_ptr<GUI> m_GUI;
	std::unique_ptr<CipherManager> m_CipherManager;
};