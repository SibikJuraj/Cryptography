#include <iostream>

#include "Application.h"
#include <Engine/Commands/ICommand.h>

#include <Engine/GUI/ImGUI.h>
#include <Engine/GUI/ImGUIElementsFactory.h>
#include <Engine/GUI/ImGUIElements.h>

Application::Application() : 
    m_GUI{ std::make_unique<ImGUI>(1600, 900) }, m_CipherManager{ std::make_unique<CipherManager>() }
{
    std::vector<const char*> cipherNames{ "Caesar" };

    ImGUIPanel* panelCiphers{ new ImGUIPanel("Ciphers") };
    panelCiphers->addElement(ImGUIComboboxCipher("Cipher", cipherNames));
    //panelCiphers->addElement(new ImGUIButton("Decrypt", new CommandCipherDecrypt()));
    //panelCiphers->addElement(new ImGUIButton("Encrypt", new CommandCipherEncrypt()));
    m_GUI->addElement(*panelCiphers);
    //TODO 
    //VYTVOR GUI JAK MA VYZERAT + NAPLN CO MA EXECUTOVAT KOMANDY ... CO SA MA VYKONAVAT
}

void Application::run()
{
    while (m_GUI->isRunning())
        m_GUI->render();
}

