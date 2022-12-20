#include "ICommands.h"

#include <GUI/GUI.h>
#include <GUI/GUIElements.h>
#include <Class Cryptography/Cryptography.h>

void CommandCipherDecrypt::execute()
{
	auto& app{ Cryptography::getInstance() };
	auto& cipher{ app.getCipher() };
	app.setOutputText(cipher.decrypt(app.getInputText()));
}

void CommandCipherEncrypt::execute()
{
	auto& app{ Cryptography::getInstance() };
	auto& cipher{ app.getCipher() };
	app.setOutputText(cipher.encrypt(app.getInputText()));
}

void CommandUpdateText::execute()
{
	auto& app{ Cryptography::getInstance() };
	auto& cipher{ app.getCipher() };
	app.setOutputText(cipher.update(app.getInputText()));
}

void CommandCipherSettings::execute()
{
	m_Panel.clear();

	auto& app{ Cryptography::getInstance() };
	auto& cipher{ app.getCipher() };

	const char* keyNames[]{ "Key 1", "Key 2", "Key 3", "Key 4", "Key 5",
		                        "Key 6", "Key 7", "Key 8", "Key 9", "Key 10",
		                        "Key 11", "Key 12", "Key 13", "Key 14", "Key 15",
		                        "Key 16", "Key 17", "Key 18", "Key 19", "Key 20",
		                        "Key 21", "Key 22", "Key 23", "Key 24", "Key 25",
		                        "Key 26", "Key 27", "Key 28", "Key 29", "Key 30",
		    };
	for (int i{ 0 }; i < cipher.getKeys().size(); ++i)
		m_Panel.addElement(app.getGUI().getElementFactory()->createInputText(keyNames[i], "", 500));
}

void CommandOpenLoadWindow::execute()
{
	Cryptography::getInstance().getGUI().openLoadWindow();
}

void CommandOpenSaveWindow::execute()
{
	Cryptography::getInstance().getGUI().openSaveWindow();
}