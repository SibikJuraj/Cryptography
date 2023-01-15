#include "Cryptography.h"

Cryptography::Cryptography(IGUIFactory& factory) 
    : m_InputText{std::make_unique<std::string>()}, 
        m_OutputText{ std::make_unique<std::string>() }
{
    m_GUI = factory.createGUI(1600, 900);
    auto cipherFactory{ m_GUI->getCipherPanelFactory() };
    
    /*m_GUI->addElement(std::move(cipherFactory->createCaesarPanel()));
    m_GUI->addElement(std::move(cipherFactory->createAffinePanel()));
    m_GUI->addElement(std::move(cipherFactory->createVigenerePanel()));
    m_GUI->addElement(std::move(cipherFactory->createHillPanel()));
    m_GUI->addElement(std::move(cipherFactory->createStreamPanel()));
    m_GUI->addElement(std::move(cipherFactory->createRSAPanel()));
    m_GUI->addElement(std::move(cipherFactory->createPwdAuthPanel()));*/
}

void Cryptography::run()
{
    while (m_GUI->isRunning())
        m_GUI->render();
}

void Cryptography::setInputText(std::string&& text)
{
    *m_InputText = text;
}

const std::string& Cryptography::getInputText()
{
    return *m_InputText;
}

void Cryptography::setOutputText(std::string&& text)
{
    *m_OutputText = text;
}

const std::string& Cryptography::getOutputText()
{
    return *m_OutputText;
}

GUI& Cryptography::getGUI() const
{
    return *m_GUI;
}