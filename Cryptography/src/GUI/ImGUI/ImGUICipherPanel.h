#pragma once

#include <vector>
#include <memory>

#include "GUI/IGUIElementsFactories.h"
#include "GUI/ImGUI/ImGUIElements.h"

template <typename K, typename T>
inline std::unique_ptr<Panel> createMainPanel(Cipher<K, T>& cipher, T& cipherInput, T& cipherOutput)
{
	auto elementFactory{ ImGUIElementsFactory() };

	auto panelCiphers{ elementFactory.createPanel("Main Panel") };

	panelCiphers->addElement(elementFactory.createButton("Decrypt", CommandCipherDecrypt(cipher, cipherInput, cipherOutput)));
	panelCiphers->addElement(elementFactory.createButton("Encrypt", CommandCipherEncrypt(cipher, cipherInput, cipherOutput)));
	panelCiphers->addElement(elementFactory.createButton("Try Find Key", CommandCipherTryFindKey(cipher, cipherInput)));

	return panelCiphers;
}

template <typename T>
inline std::unique_ptr<Panel> createCipherInputPanel(T& cipherInput)
{
	auto elementFactory{ ImGUIElementsFactory() };

	auto panelInputText{ elementFactory.createPanel("Input Text") };
	panelInputText->addElement(std::move(elementFactory.createButton("Load File", CommandOpenImGUILoadWindow())));
	panelInputText->addElement(std::move(elementFactory.createTextbox("Input Text", cipherInput)));

	return panelInputText;
}

template <typename T>
inline std::unique_ptr<Panel> createCipherOutputPanel(T& cipherOutput)
{
	auto elementFactory{ ImGUIElementsFactory() };

	auto panelOutputText{ elementFactory.createPanel("Output Text") };
	panelOutputText->addElement(std::move(elementFactory.createButton("Save File", CommandOpenImGUISaveWindow())));
	panelOutputText->addElement(std::move(elementFactory.createTextbox("Output Text", cipherOutput)));

	return panelOutputText;
}

class ImGUICaesarPanel : public CaesarPanel
{
public:
	ImGUICaesarPanel() : CaesarPanel()
	{
		addElement(createMainPanel(m_Cipher, m_CipherInput, m_CipherOutput));
		addElement(createCipherInputPanel(m_CipherInput));
		addElement(createCipherOutputPanel(m_CipherOutput));
		addElement(std::make_unique<ImGUIFileLoaderPanel<std::string>>("File Loader", m_CipherInput, m_CipherOutput, std::make_unique<StringLoader>()));

		auto elementFactory{ ImGUIElementsFactory() };
		addElement(elementFactory.createInputInt("Key 1", m_Cipher.getKey().k1, CommandUpdateText(m_Cipher, m_CipherInput, m_CipherOutput)));
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
		addElement(createMainPanel(m_Cipher, m_CipherInput, m_CipherOutput));
		addElement(createCipherInputPanel(m_CipherInput));
		addElement(createCipherOutputPanel(m_CipherOutput));
		addElement(std::make_unique<ImGUIFileLoaderPanel<std::string>>("File Loader", m_CipherInput, m_CipherOutput, std::make_unique<StringLoader>()));

		auto elementFactory{ ImGUIElementsFactory() };
		addElement(elementFactory.createInputInt("Key 1", m_Cipher.getKey().k1, CommandUpdateText(m_Cipher, m_CipherInput, m_CipherOutput)));
		addElement(elementFactory.createInputInt("Key 2", m_Cipher.getKey().k2, CommandUpdateText(m_Cipher, m_CipherInput, m_CipherOutput)));
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
	ImGUIVigenerePanel() : m_MainPanels{ 0 }, VigenerePanel()
	{
		auto elementFactory{ ImGUIElementsFactory() };

		addElement(createMainPanel(m_Cipher, m_CipherInput, m_CipherOutput));
		addElement(createCipherInputPanel(m_CipherInput));
		addElement(createCipherOutputPanel(m_CipherOutput));
		addElement(std::make_unique<ImGUIFileLoaderPanel<std::string>>("File Loader", m_CipherInput, m_CipherOutput, std::make_unique<StringLoader>()));

		addElement(elementFactory.createButton("Add", CommandAddInputInt(m_Cipher.getKey().keys)));
		addElement(elementFactory.createButton("Remove", CommandRemoveInputInt(m_Cipher.getKey().keys)));
		
		m_MainPanels = m_Elements.size();
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

		if (m_Elements.size() != m_MainPanels + m_Cipher.getKey().keys.size())
		{
			for (int i = m_Elements.size(); i > m_MainPanels; --i)
			{
				m_Elements.pop_back();
			}
			for (int i = 0; i < m_Cipher.getKey().keys.size(); ++i)
			{
				addElement(elementFactory.createInputInt(keyNames[i], m_Cipher.getKey().keys[i], CommandUpdateText(m_Cipher, m_CipherInput, m_CipherOutput)));
			}
		}

		ImGui::Begin(m_Label);

		for (int i{ 0 }; i < m_Elements.size(); ++i)
			m_Elements[i]->draw();

		ImGui::End();
	}
private:
	int m_MainPanels;
};

class ImGUIHillPanel : public HillPanel
{
public:
	ImGUIHillPanel() : HillPanel()
	{
		auto elementFactory{ ImGUIElementsFactory() };

		addElement(createMainPanel(m_Cipher, m_CipherInput, m_CipherOutput));
		addElement(createCipherInputPanel(m_CipherInput));
		addElement(createCipherOutputPanel(m_CipherOutput));
		addElement(std::make_unique<ImGUIFileLoaderPanel<std::string>>("File Loader", m_CipherInput, m_CipherOutput, std::make_unique<StringLoader>()));

		m_MainPanels = m_Elements.size();
	}
	virtual void draw() override
	{
		ImGui::Begin(m_Label);

		for (int i{ 0 }; i < m_Elements.size(); ++i)
			m_Elements[i]->draw();

		ImGui::End();
	}
private:
	int m_MainPanels;
};

class ImGUIStreamPanel : public StreamPanel
{
public:
	ImGUIStreamPanel() : StreamPanel()
	{
		addElement(createMainPanel(m_Cipher, m_CipherInput, m_CipherOutput));
		addElement(createCipherInputPanel(m_CipherInput));
		addElement(createCipherOutputPanel(m_CipherOutput));
		addElement(std::make_unique<ImGUIFileLoaderPanel<std::string>>("File Loader", m_CipherInput, m_CipherOutput, std::make_unique<StringLoader>()));

		auto elementFactory{ ImGUIElementsFactory() };
		addElement(elementFactory.createInputInt("Key 1", m_Cipher.getKey().seed, CommandUpdateText(m_Cipher, m_CipherInput, m_CipherOutput)));

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
		addElement(createMainPanel(m_Cipher, m_CipherInput, m_CipherOutput));
		addElement(createCipherInputPanel(m_CipherInput));
		addElement(createCipherOutputPanel(m_CipherOutput));
		addElement(std::make_unique<ImGUIFileLoaderPanel<std::string>>("File Loader", m_CipherInput, m_CipherOutput, std::make_unique<StringLoader>()));

		auto elementFactory{ ImGUIElementsFactory() };
		addElement(elementFactory.createInputText("Key pub e", m_Cipher.getKey().pubKey[0], CommandUpdateText(m_Cipher, m_CipherInput, m_CipherOutput)));
		addElement(elementFactory.createInputText("Key pub n", m_Cipher.getKey().pubKey[1], CommandUpdateText(m_Cipher, m_CipherInput, m_CipherOutput)));
		addElement(elementFactory.createInputText("Key pri d", m_Cipher.getKey().priKey[0], CommandUpdateText(m_Cipher, m_CipherInput, m_CipherOutput)));
		addElement(elementFactory.createInputText("Key pri n", m_Cipher.getKey().priKey[1], CommandUpdateText(m_Cipher, m_CipherInput, m_CipherOutput)));

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
		addElement(createMainPanel(m_Cipher, m_CipherInput, m_CipherOutput));
		addElement(createCipherInputPanel(m_CipherInput));
		addElement(createCipherOutputPanel(m_CipherOutput));
		addElement(std::make_unique<ImGUIFileLoaderPanel<std::string>>("File Loader", m_CipherInput, m_CipherOutput, std::make_unique<StringLoader>()));

	}
	virtual void draw() override
	{
		ImGui::Begin(m_Label);

		for (int i{ 0 }; i < m_Elements.size(); ++i)
			m_Elements[i]->draw();

		ImGui::End();
	}
};