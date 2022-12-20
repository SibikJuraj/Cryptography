#include <iostream>
#include <utility>
#include "Cryptography.h"
#include <Text/TextLoader.h>

#include <Ciphers/Caesar.h>
#include <Ciphers/Affine.h>
#include <Ciphers/Vigenere.h>
#include <Ciphers/Hill.h>
#include <Ciphers/Stream.h>
#include <Ciphers/RSA.h>
#include <Ciphers/PwdAuth.h>

Cryptography::Cryptography(IGUIFactory& factory) : m_SelectedCipher{ 0 },
    m_InputText{std::make_unique<std::string>()}, m_OutputText{ std::make_unique<std::string>() }
{
    registerCipher(std::make_unique<Caesar>());
    registerCipher(std::make_unique<Affine>());
    registerCipher(std::make_unique<Vigenere>());
    registerCipher(std::make_unique<Stream>());
    registerCipher(std::make_unique<Hill>());
    registerCipher(std::make_unique<RSA>());
    registerCipher(std::make_unique<PwdAuth>());

    std::vector<const char*> cipherNames;

    for (auto& cipher : m_Ciphers)
    {
        cipherNames.push_back(cipher->getName());
    }

    m_GUI = factory.createGUI(1600, 900);
    auto elementFactory{ m_GUI->getElementFactory() };

    auto panelCipherParameters{ elementFactory->createPanel("Cipher parameters") };

    auto decryptContainer{ std::make_shared<CommandContainer>() };
    decryptContainer->addElement(std::make_shared<CommandCipherDecrypt>());
    decryptContainer->addElement(std::make_shared<CommandCipherSettings>(*panelCipherParameters));

    auto encryptContainer{ std::make_shared<CommandContainer>() };
    encryptContainer->addElement(std::make_shared<CommandCipherEncrypt>());
    encryptContainer->addElement(std::make_shared<CommandCipherSettings>(*panelCipherParameters));

    auto panelCiphers{ elementFactory->createPanel("Main Panel") };
    panelCiphers->addElement(std::move(elementFactory->createCombobox("Cipher", cipherNames, m_SelectedCipher, CommandCipherSettings(*panelCipherParameters))));
    panelCiphers->addElement(std::move(elementFactory->createButton("Decrypt", std::move(*decryptContainer))));
    panelCiphers->addElement(std::move(elementFactory->createButton("Encrypt", std::move(*encryptContainer))));
    
    auto panelInputText{ elementFactory->createPanel("Input Text") };
    panelInputText->addElement(std::move(elementFactory->createButton("Load File", CommandOpenLoadWindow())));
    panelInputText->addElement(std::move(elementFactory->createTextbox("Input Text", *m_InputText)));

    auto panelOutputText{ elementFactory->createPanel("Output Text") };
    panelOutputText->addElement(std::move(elementFactory->createButton("Save File", CommandOpenSaveWindow())));
    panelOutputText->addElement(std::move(elementFactory->createTextbox("Output Text", *m_OutputText)));
    
    m_GUI->addElement(std::move(panelCiphers));
    m_GUI->addElement(std::move(panelInputText));
    m_GUI->addElement(std::move(panelOutputText));
    m_GUI->addElement(std::move(panelCipherParameters));
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

Cipher<>& Cryptography::getCipher() const
{
    return *m_Ciphers[m_SelectedCipher];
}

GUI& Cryptography::getGUI() const
{
    return *m_GUI;
}

void Cryptography::registerCipher(std::unique_ptr<Cipher<>>&& cipher)
{
    m_Ciphers.emplace_back(std::move(cipher));
}
