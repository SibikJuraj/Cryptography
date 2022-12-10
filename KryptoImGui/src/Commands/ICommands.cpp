#include "ICommands.h"

#include <GUI/GUI.h>

void CommandOpenLoadWindow::execute()
{
	m_GUI.openLoadWindow();
}

void CommandOpenSaveWindow::execute()
{
	m_GUI.openSaveWindow();
}