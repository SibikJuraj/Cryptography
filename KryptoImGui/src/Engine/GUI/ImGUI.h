#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GUI.h"

class ImGUI : public GUI
{
public:
	ImGUI(int width, int height);
	~ImGUI();
	GLFWwindow* getWindow();

	virtual void preRun() override;
	virtual void run() override;
	virtual void postRun() override;
	virtual bool isRunning() override;
	virtual void addElement(IGUIElement* element) override;
private:
	GLFWwindow* m_Window;
	int m_SelectedOption;

	void imGuiRender();
};