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
    registerCipher(new Caesar());
    registerCipher(new Affine());
    registerCipher(new Vigenere());
    registerCipher(new Stream());
    registerCipher(new Hill());
    registerCipher(new RSA());
    registerCipher(new PwdAuth());

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
    panelInputText->addElement(std::move(elementFactory->createButton("Load File", CommandOpenLoadWindow(std::move(*m_GUI)))));
    panelInputText->addElement(std::move(elementFactory->createTextbox("Input Text", *m_InputText)));

    auto panelOutputText{ elementFactory->createPanel("Output Text") };
    panelOutputText->addElement(std::move(elementFactory->createButton("Save File", CommandOpenSaveWindow(std::move(*m_GUI)))));
    panelOutputText->addElement(std::move(elementFactory->createTextbox("Output Text", *m_OutputText)));
    
    m_GUI->addElement(std::move(panelCiphers));
    m_GUI->addElement(std::move(panelInputText));
    m_GUI->addElement(std::move(panelOutputText));
    m_GUI->addElement(std::move(panelCipherParameters));
}

void Cryptography::run()
{
    /*auto textVigenere{ TextLoader::loadText("texts/vigenere/text1_enc.txt") };
    auto decryptedTextVigenere{ Viegener().decrypt(textVigenere) };
    TextLoader::saveText("texts/vigenere/decoded/text1_dec.txt", decryptedTextVigenere);

    auto textStream{ TextLoader::loadText("texts/stream/text1_enc.txt") };
    auto decryptedTextStream{ Stream().decrypt(textStream) };
    TextLoader::saveText("texts/stream/decoded/text1_dec.txt", decryptedTextStream); */

    /*auto textHill{ TextLoader::loadText("texts/hill/text3_enc.txt") };
    auto decryptedTextHill{ Hill({ 3, 7, 20, 17, 24, 17, 0, 9, 0 }).decrypt(textHill) };
    TextLoader::saveText("texts/hill/decoded/text3_dec.txt", decryptedTextHill);*/

    /*auto textMD5{ TextLoader::loadText("texts/md5/shadow1.txt") };
    auto decryptedTextMD5{ PwdAuth::decrypt(textMD5) };
    TextLoader::saveText("texts/md5/decoded/shadow1_pwd.txt", decryptedTextMD5, true);*/

    /*RSA rsa;
    rsa.decrypt("");*/
    
    while (m_GUI->isRunning())
    {
        m_GUI->render();
    }
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

void Cryptography::registerCipher(Cipher<>* cipher)
{
    m_Ciphers.emplace_back(std::move(cipher));
}
