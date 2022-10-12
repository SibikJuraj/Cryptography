#pragma once

#include <memory>
#include "OpenGLWindow.h"

class Application
{
public:
	Application();
	void run();
	virtual ~Application();
private:
	std::unique_ptr<OpenGLWindow> m_Window;
};