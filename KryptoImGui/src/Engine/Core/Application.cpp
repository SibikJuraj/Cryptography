#include <iostream>

#include "Application.h"
#include "Ciphers/Caesar.h"
#include "Ciphers/Affine.h"
#include "Ciphers/Viegener.h"

#include <Engine/GUI/ImGUI.h>
#include <Engine/GUI/ImGUIFactory.h>
#include <Engine/GUI/ImGUIElements.h>
#include <Engine/Commands/ICommand.h>

Application::Application() : 
    m_GUI{ std::make_unique<ImGUI>(1600, 900) }, m_CurrentCipher{ 0 },
    m_English{ false }
{
    CipherManager::getInstance().registerCipher(new Caesar());
    CipherManager::getInstance().registerCipher(new Affine());
    CipherManager::getInstance().registerCipher(new Viegener());
    std::vector<const char*> cipherNames{ "Affine", "Caesar" };

    ImGUIPanel* panelCiphers{ new ImGUIPanel("Ciphers") };
    panelCiphers->addElement(new ImGUIComboboxCipher("Cipher", cipherNames));
    panelCiphers->addElement(new ImGUIButton("Decrypt", new CommandCipherDecrypt()));
    panelCiphers->addElement(new ImGUIButton("Encrypt", new CommandCipherEncrypt()));
    panelCiphers->addElement(new ImGUICheckbox("English", m_English));
    m_GUI->addElement(panelCiphers);
    //TODO 
    //VYTVOR GUI JAK MA VYZERAT + NAPLN CO MA EXECUTOVAT KOMANDY ... CO SA MA VYKONAVAT
}

void Application::run()
{

    while (m_GUI->isRunning())
    {
        m_GUI->preRun();
        m_GUI->run();
        m_GUI->postRun();
    }
}

Application::~Application()
{
}


void Application::createCipherClass(int selectedOption)
{
    switch (selectedOption)
    {
       /* case 0:
            m_Cipher = std::move(std::make_unique<Caesar>());
            break;
        case 1:
            m_Cipher = std::move(std::make_unique<Affine>());
            break;
        case 2:
            m_Cipher = std::move(std::make_unique<Viegener>());
            break;*/
    }
}

