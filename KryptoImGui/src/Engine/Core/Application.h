#pragma once

#include <memory>
#include "OpenGLWindow.h"
#include "../FileLoader.h"
#include "../../Ciphers/Cipher.h"

class Application
{
public:
	Application();
	void run();
	~Application();

	std::unique_ptr<Cipher> createCipherClass();
private:
	std::unique_ptr<OpenGLWindow> m_Window;
	std::unique_ptr<FileLoader> m_File;
	std::unique_ptr<Cipher> m_Cipher;
	int m_SelectedOption;
};