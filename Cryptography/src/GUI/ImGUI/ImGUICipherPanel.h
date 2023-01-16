#pragma once

#include <vector>
#include <memory>

#include "GUI/IGUIElementsFactories.h"
#include "GUI/ImGUI/ImGUIElements.h"

inline std::unique_ptr<Panel> createMainPanel(ICipher& cipher)
{
	auto elementFactory{ ImGUIElementsFactory() };

	auto panelCiphers{ elementFactory.createPanel("Main Panel") };

	panelCiphers->addElement(elementFactory.createButton("Decrypt", CommandCipherDecrypt(cipher)));
	panelCiphers->addElement(elementFactory.createButton("Encrypt", CommandCipherEncrypt(cipher)));
	panelCiphers->addElement(elementFactory.createButton("Try Find Key", CommandCipherTryFindKey(cipher)));

	return panelCiphers;
}

class ImGUICaesarPanel : public CaesarPanel
{
public:
	ImGUICaesarPanel() : CaesarPanel()
	{
		auto elementFactory{ ImGUIElementsFactory() };

		addElement(createMainPanel(m_Cipher));

		//addElement(elementFactory.createButton("Add", CommandAddInputInt(m_Cipher.getKey().keys)));
		//addElement(elementFactory.createButton("Remove", );

		/*auto panels{ initCipherPanel() };
		for (auto& el : panels)
			addElement(std::move(el));*/

		addElement(elementFactory.createInputInt("Key 1", m_Cipher.getKey().k1, CommandUpdateText(m_Cipher)));

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
		auto elementFactory{ ImGUIElementsFactory() };

		addElement(createMainPanel(m_Cipher));
		//addElement(elementFactory.createButton("Add", CommandAddInputInt(m_Cipher.getKey().keys)));
		//addElement(elementFactory.createButton("Remove", );

		/*auto panels{ initCipherPanel() };
		for (auto& el : panels)
			addElement(std::move(el));*/

		addElement(elementFactory.createInputInt("Key 1", m_Cipher.getKey().k1, CommandUpdateText(m_Cipher)));
		addElement(elementFactory.createInputInt("Key 2", m_Cipher.getKey().k2, CommandUpdateText(m_Cipher)));

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
	ImGUIVigenerePanel() :m_KeyPanel { ImGUIPanel("Cipherparam") }, VigenerePanel()
	{
		auto elementFactory{ ImGUIElementsFactory() };

		addElement(createMainPanel(m_Cipher));
		//addElement(elementFactory.createButton("Add", CommandAddInputInt(m_Cipher.getKey().keys)));
		//addElement(elementFactory.createButton("Remove", );
		
		/*auto panels{ initCipherPanel() };
		for (auto& el : panels)
			addElement(std::move(el));*/

		const char* keyNames[]{ "Key 1", "Key 2", "Key 3", "Key 4", "Key 5",
								"Key 6", "Key 7", "Key 8", "Key 9", "Key 10",
								"Key 11", "Key 12", "Key 13", "Key 14", "Key 15",
								"Key 16", "Key 17", "Key 18", "Key 19", "Key 20",
								"Key 21", "Key 22", "Key 23", "Key 24", "Key 25",
								"Key 26", "Key 27", "Key 28", "Key 29", "Key 30",
		};
		for (int i{ 0 }; i < m_Cipher.getKey().keys.size(); ++i)
			m_KeyPanel.addElement(elementFactory.createInputInt(keyNames[i], m_Cipher.getKey().keys[i], CommandUpdateText(m_Cipher)));

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
			m_KeyPanel.clear();
			for (int i{ 0 }; i < m_Cipher.getKey().keys.size(); ++i)
				m_KeyPanel.addElement(elementFactory.createInputInt(keyNames[i], m_Cipher.getKey().keys[i], CommandUpdateText(m_Cipher)));
		}

		ImGui::Begin(m_Label);

		for (int i{ 0 }; i < m_Elements.size(); ++i)
			m_Elements[i]->draw();

		m_KeyPanel.draw();

		ImGui::End();
	}
private:
	ImGUIPanel m_KeyPanel;
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