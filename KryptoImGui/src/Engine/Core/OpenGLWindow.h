#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>

class OpenGLWindow
{
public:
	OpenGLWindow(int width, int height);
	~OpenGLWindow();
	GLFWwindow* getWindow();
private:
	GLFWwindow* m_Window;
};