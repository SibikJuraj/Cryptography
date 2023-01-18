#pragma once
#include "GUI/GUI.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ImGUI : public GUI
{
public:
	ImGUI(int width, int height);
	~ImGUI();

	virtual void render() override;
	virtual bool isRunning() override;
	virtual void addElement(std::unique_ptr<Panel>&& element) override;
	virtual void addCipherPanel(std::unique_ptr<ICipherPanel>&& panel) override;
	virtual std::unique_ptr<CipherPanelFactory> getCipherPanelFactory() override;
	virtual std::unique_ptr<IGUIElementsFactory> getElementFactory() override;

private:
	GLFWwindow* m_Window;

	void imGuiRender();
};