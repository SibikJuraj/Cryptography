#pragma once

#include "GUI/IGUIElementsFactories.h"
#include "GUI/ImGUI/ImGUIElements.h"

//void initCipherPanel()
//{
//	auto elementFactory{ ImGUIElementsFactory() };
//
//	auto panelCipherParameters{ elementFactory.createPanel("Cipher parameters") };
//
//	auto decryptContainer{ std::make_shared<CommandContainer>() };
//	//decryptContainer->addElement(std::make_shared<CommandCipherDecrypt>());
//	//decryptContainer->addElement(std::make_shared<CommandCipherSettings>(*panelCipherParameters));
//
//	auto encryptContainer{ std::make_shared<CommandContainer>() };
//	//encryptContainer->addElement(std::make_shared<CommandCipherEncrypt>());
//	//encryptContainer->addElement(std::make_shared<CommandCipherSettings>(*panelCipherParameters));
//
//	auto panelCiphers{ elementFactory.createPanel("Main Panel") };
//	//panelCiphers->addElement(std::move(elementFactory->createCombobox("Cipher", cipherNames, m_SelectedCipher, CommandCipherSettings(*panelCipherParameters))));
//	panelCiphers->addElement(std::move(elementFactory.createButton("Decrypt", std::move(*decryptContainer))));
//	panelCiphers->addElement(std::move(elementFactory.createButton("Encrypt", std::move(*encryptContainer))));
//
//	auto panelInputText{ elementFactory.createPanel("Input Text") };
//	panelInputText->addElement(std::move(elementFactory.createButton("Load File", CommandOpenLoadWindow())));
//	//panelInputText->addElement(std::move(elementFactory->createTextbox("Input Text", *m_InputText)));
//
//	auto panelOutputText{ elementFactory.createPanel("Output Text") };
//	panelOutputText->addElement(std::move(elementFactory.createButton("Save File", CommandOpenSaveWindow())));
//	//panelOutputText->addElement(std::move(elementFactory->createTextbox("Output Text", *m_OutputText)));
//
//	//return {
//	//	std::move(panelCiphers), std::move(panelInputText),
//	//	std::move(panelOutputText), std::move(panelCipherParameters)
//	//};
//}

class ImGUICaesarPanel : public CaesarPanel
{
public:
	ImGUICaesarPanel() : CaesarPanel()
	{
		/*auto panels{ initCipherPanel() };
		for (auto& el: panels)
			addElement(std::move(el));*/
	}

	virtual void draw() override
	{
		ImGui::Begin(m_Label);

		for (int i{ 0 }; i < m_Elements.size(); ++i)
			m_Elements[i]->draw();

		ImGui::End();
	}
};

class ImGUIAffinePanel : public AffinePanel
{
public:
	ImGUIAffinePanel() : AffinePanel()
	{
		/*auto panels{ initCipherPanel() };
		for (auto& el : panels)
			addElement(std::move(el));*/
	}
	virtual void draw() override
	{
		ImGui::Begin(m_Label);

		for (int i{ 0 }; i < m_Elements.size(); ++i)
			m_Elements[i]->draw();

		ImGui::End();
	}
};

class ImGUIVigenerePanel : public VigenerePanel
{
public:
	ImGUIVigenerePanel() : VigenerePanel()
	{
		/*auto panels{ initCipherPanel() };
		for (auto& el : panels)
			addElement(std::move(el));*/
	}
	virtual void draw() override
	{
		ImGui::Begin(m_Label);

		for (int i{ 0 }; i < m_Elements.size(); ++i)
			m_Elements[i]->draw();

		ImGui::End();
	}
};

class ImGUIHillPanel : public HillPanel
{
public:
	ImGUIHillPanel() : HillPanel()
	{
		/*auto panels{ initCipherPanel() };
		for (auto& el : panels)
			addElement(std::move(el));*/
	}
	virtual void draw() override
	{
		ImGui::Begin(m_Label);

		for (int i{ 0 }; i < m_Elements.size(); ++i)
			m_Elements[i]->draw();

		ImGui::End();
	}
};

class ImGUIStreamPanel : public StreamPanel
{
public:
	ImGUIStreamPanel() : StreamPanel()
	{
		/*auto panels{ initCipherPanel() };
		for (auto& el : panels)
			addElement(std::move(el));*/
	}
	virtual void draw() override
	{
		ImGui::Begin(m_Label);

		for (int i{ 0 }; i < m_Elements.size(); ++i)
			m_Elements[i]->draw();

		ImGui::End();
	}
};

class ImGUIRSAPanel : public RSAPanel
{
public:
	ImGUIRSAPanel() : RSAPanel()
	{
		/*auto panels{ initCipherPanel() };
		for (auto& el : panels)
			addElement(std::move(el));*/
	}
	virtual void draw() override
	{
		ImGui::Begin(m_Label);

		for (int i{ 0 }; i < m_Elements.size(); ++i)
			m_Elements[i]->draw();

		ImGui::End();
	}
};

class ImGUIPwdAuthPanel : public PwdAuthPanel
{
public:
	ImGUIPwdAuthPanel() : PwdAuthPanel()
	{
		/*auto panels{ initCipherPanel() };
		for (auto& el : panels)
			addElement(std::move(el));*/
	}
	virtual void draw() override
	{
		ImGui::Begin(m_Label);

		for (int i{ 0 }; i < m_Elements.size(); ++i)
			m_Elements[i]->draw();

		ImGui::End();
	}
};