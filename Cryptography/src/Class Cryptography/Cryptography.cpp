#include "Cryptography.h"

Cryptography::Cryptography(IGUIFactory& factory) 
    : m_CurrentCipher{ 0 }
{
    m_GUI = factory.createGUI(1600, 900);
    auto cipherFactory{ m_GUI->getCipherPanelFactory() };
    auto elementFactory{ m_GUI->getElementFactory() };
    
    std::vector<std::string> cipherNames;

    //Here add new cipher panels
    addCipher(cipherNames, std::move(cipherFactory->createCaesarPanel()));
    addCipher(cipherNames, std::move(cipherFactory->createAffinePanel()));
    addCipher(cipherNames, std::move(cipherFactory->createVigenerePanel()));
    addCipher(cipherNames, std::move(cipherFactory->createHillPanel()));
    addCipher(cipherNames, std::move(cipherFactory->createStreamPanel()));
    addCipher(cipherNames, std::move(cipherFactory->createRSAPanel()));
    addCipher(cipherNames, std::move(cipherFactory->createPwdAuthPanel()));


    auto panelCiphers{ elementFactory->createPanel("Ciphers") };
    panelCiphers->addElement(std::move(elementFactory->createCombobox("Cipher", cipherNames, m_CurrentCipher)));
   
    m_GUI->addElement(std::move(panelCiphers));
}

void Cryptography::run()
{
    while (m_GUI->isRunning())
        m_GUI->render();
}


GUI& Cryptography::getGUI() const
{
    return *m_GUI;
}

void Cryptography::setCurrentCipher(int&& cipher)
{
    m_CurrentCipher = cipher;
}

const int& Cryptography::getCurrentCipher()
{
    return m_CurrentCipher;
}

void Cryptography::addCipher(std::vector<std::string>& cipherNames, std::unique_ptr<ICipherPanel>&& panel)
{
    cipherNames.push_back(panel->getCipherName());
    m_GUI->addCipherPanel(std::move(panel));
}