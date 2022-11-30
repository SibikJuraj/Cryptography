#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GUI.h"

class ImGUI : public GUI
{
public:
	ImGUI(int width, int height);
	~ImGUI();

	virtual void render() override;
	virtual bool isRunning() override;
	virtual void addElement(IGUIElement& element) override;
private:
	std::unique_ptr<GLFWwindow> m_Window;
	int m_SelectedOption;

	void imGuiRender();
};