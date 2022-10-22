#include "OpenGLWindow.h"
#include <iostream>

OpenGLWindow::OpenGLWindow(int width, int height)
{
    m_Window = glfwCreateWindow(width, height, "Kryptografia a bezpecnost", NULL, NULL) ;
    if (m_Window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return; //-1;
    }
}

OpenGLWindow::~OpenGLWindow()
{
    glfwDestroyWindow(m_Window);
    m_Window = nullptr;
}

GLFWwindow* OpenGLWindow::getWindow()
{
    return m_Window;
}
