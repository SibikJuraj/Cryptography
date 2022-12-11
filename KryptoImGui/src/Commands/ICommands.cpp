#include "ICommands.h"

#include <GUI/GUI.h>
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

void CommandOpenLoadWindow::execute()
{
	m_GUI.openLoadWindow();
}

void CommandOpenSaveWindow::execute()
{
	m_GUI.openSaveWindow();
}