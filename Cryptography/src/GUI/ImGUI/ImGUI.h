#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <GUI/GUI.h>

class ImGUI : public GUI
{
public:
	ImGUI(int width, int height);
	~ImGUI();

	virtual void render() override;
	virtual bool isRunning() override;
	virtual void addElement(std::unique_ptr<IGUIElement>&& element) override;
	virtual std::unique_ptr<IGUIElementsFactory> getElementFactory() override;

	virtual void openSaveWindow() override;
	virtual void openLoadWindow() override;
private:
	GLFWwindow* m_Window;

	void imGuiRender();
	void fileWindowRender();
};