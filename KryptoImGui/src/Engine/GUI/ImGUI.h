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
	virtual void run(std::vector<const char*> items, const char* curItem,
		int& selectedCipher, Text& iText, Text& oText, bool& fineTuning, bool& enLanguage) override;
	virtual void postRun() override;
	virtual bool isRunning() override;

private:
	GLFWwindow* m_Window;
	int m_SelectedOption;

	void imGuiRender();
};