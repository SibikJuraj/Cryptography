#pragma once

#include <vector>
#include <memory>

#include "GUI/IGUIElementsFactories.h"
#include "GUI/ImGUI/ImGUIElements.h"

inline std::vector<std::unique_ptr<ImGUIPanel>> initCipherPanel()
{
	auto elementFactory{ ImGUIElementsFactory() };

	auto panelCipherParameters{ elementFactory.createPanel("Cipher parameters") };

	auto decryptContainer{ std::make_shared<CommandContainer>() };
	//decryptContainer->addElement(std::make_shared<CommandCipherDecrypt>());
	//decryptContainer->addElement(std::make_shared<CommandCipherSettings>(*panelCipherParameters));

	auto encryptContainer{ std::make_shared<CommandContainer>() };
	//encryptContainer->addElement(std::make_shared<CommandCipherEncrypt>());
	//encryptContainer->addElement(std::make_shared<CommandCipherSettings>(*panelCipherParameters));

	auto panelCiphers{ elementFactory.createPanel("Main Panel") };
	//panelCiphers->addElement(std::move(elementFactory->createCombobox("Cipher", cipherNames, m_SelectedCipher, CommandCipherSettings(*panelCipherParameters))));
	panelCiphers->addElement(std::move(elementFactory.createButton("Decrypt", std::move(*decryptContainer))));
	panelCiphers->addElement(std::move(elementFactory.createButton("Encrypt", std::move(*encryptContainer))));

	auto panelInputText{ elementFactory.createPanel("Input Text") };
	panelInputText->addElement(std::move(elementFactory.createButton("Load File", CommandOpenLoadWindow())));
	//panelInputText->addElement(std::move(elementFactory->createTextbox("Input Text", *m_InputText)));

	auto panelOutputText{ elementFactory.createPanel("Output Text") };
	panelOutputText->addElement(std::move(elementFactory.createButton("Save File", CommandOpenSaveWindow())));
	//panelOutputText->addElement(std::move(elementFactory->createTextbox("Output Text", *m_OutputText)));

	std::vector<std::unique_ptr<ImGUIPanel>> vec{};
	//vec.emplace_back(std::move(panelCiphers));
	//vec.emplace_back(std::move(panelInputText));
	//vec.emplace_back(std::move(panelOutputText));
	//vec.emplace_back(std::move(panelCipherParameters));

	return vec;
}

class ImGUICaesarPanel : public CaesarPanel
{
public:
	ImGUICaesarPanel() : CaesarPanel()
	{
		//auto elementFactory{ ImGUIElementsFactory() };

		//auto decryptContainer{ std::make_shared<CommandContainer>() };
		//decryptContainer->addElement(std::make_shared<CommandCipherDecrypt>(m_Cipher));
		////decryptContainer->addElement(std::make_shared<CommandCipherSettings>(*panelCipherParameters));

		//auto encryptContainer{ std::make_shared<CommandContainer>() };
		//encryptContainer->addElement(std::make_shared<CommandCipherEncrypt>(m_Cipher));
		////encryptContainer->addElement(std::make_shared<CommandCipherSettings>(*panelCipherParameters));

		//auto panelCiphers{ elementFactory.createPanel("Main Panel") };
		////panelCiphers->addElement(std::move(elementFactory->createCombobox("Cipher", cipherNames, m_SelectedCipher, CommandCipherSettings(*panelCipherParameters))));
		//panelCiphers->addElement(std::move(elementFactory.createButton("Decrypt", std::move(*decryptContainer))));
		//panelCiphers->addElement(std::move(elementFactory.createButton("Encrypt", std::move(*encryptContainer))));

		//addElement(std::move(panelCiphers));

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
		auto elementFactory{ ImGUIElementsFactory() };

		auto decryptContainer{ std::make_shared<CommandContainer>() };
		decryptContainer->addElement(std::make_shared<CommandCipherDecrypt>(m_Cipher));
		//decryptContainer->addElement(std::make_shared<CommandCipherSettings>(*panelCipherParameters));

		auto encryptContainer{ std::make_shared<CommandContainer>() };
		encryptContainer->addElement(std::make_shared<CommandCipherEncrypt>(m_Cipher));
		//encryptContainer->addElement(std::make_shared<CommandCipherSettings>(*panelCipherParameters));

		auto tryFindKeyContainer{ std::make_shared<CommandContainer>() };
		tryFindKeyContainer->addElement(std::make_shared<CommandCipherTryFindKey>(m_Cipher));


		auto panelCiphers{ elementFactory.createPanel("Main Panel") };
		//panelCiphers->addElement(std::move(elementFactory->createCombobox("Cipher", cipherNames, m_SelectedCipher, CommandCipherSettings(*panelCipherParameters))));
		panelCiphers->addElement(std::move(elementFactory.createButton("Decrypt", std::move(*decryptContainer))));
		panelCiphers->addElement(std::move(elementFactory.createButton("Encrypt", std::move(*encryptContainer))));
		panelCiphers->addElement(std::move(elementFactory.createButton("Try Find Key", std::move(*tryFindKeyContainer))));

		addElement(std::move(panelCiphers));
		//addElement(elementFactory.createButton("Add", CommandAddInputInt(m_Cipher.getKey().keys)));
		//addElement(elementFactory.createButton("Remove", );

		/*auto panels{ initCipherPanel() };
		for (auto& el : panels)
			addElement(std::move(el));*/
	}
	virtual void draw() override
	{
		auto elementFactory{ ImGUIElementsFactory() };
		const char* keyNames[]{ "Key 1", "Key 2", "Key 3", "Key 4", "Key 5",
								"Key 6", "Key 7", "Key 8", "Key 9", "Key 10",
								"Key 11", "Key 12", "Key 13", "Key 14", "Key 15",
								"Key 16", "Key 17", "Key 18", "Key 19", "Key 20",
								"Key 21", "Key 22", "Key 23", "Key 24", "Key 25",
								"Key 26", "Key 27", "Key 28", "Key 29", "Key 30",
		};
		if (m_Cipher.getKey().keys.size() != m_Elements.size() - 1)
		{
			for (int i{ 0 }; i < m_Cipher.getKey().keys.size(); ++i)
				addElement(elementFactory.createInputInt(keyNames[i], m_Cipher.getKey().keys[i], CommandUpdateText(m_Cipher)));
		}

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