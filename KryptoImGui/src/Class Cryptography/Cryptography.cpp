#include <iostream>
#include <utility>
#include "Cryptography.h"

#include <Ciphers/Caesar.h>
#include <Ciphers/Affine.h>
#include <Ciphers/Viegener.h>
#include <Ciphers/Hill.h>
#include <Ciphers/Stream.h>
#include <Ciphers/RSA.h>
#include <Text/TextLoader.h>
#include <PwdAuth.h>

Cryptography::Cryptography(IGUIFactory& factory) :
    m_InputText{std::make_unique<std::string>()}, m_OutputText{ std::make_unique<std::string>() }
{
    registerCipher(new Caesar());
    registerCipher(new Affine());
    registerCipher(new Viegener());
    registerCipher(new Stream());
    registerCipher(new Hill());
    registerCipher(new RSA());

    std::vector<const char*> cipherNames;

    for (auto& cipher : m_Ciphers)
    {
        cipherNames.push_back(cipher->getName());
    }

    m_GUI = factory.createGUI(1600, 900);
    auto elementFactory{ m_GUI->getElementFactory() };

    auto panelCiphers{ elementFactory->createPanel("Main Panel") };
    panelCiphers->addElement(std::move(elementFactory->createCombobox("Cipher", cipherNames)));
    panelCiphers->addElement(std::move(elementFactory->createButton("Decrypt", CommandCipherDecrypt())));
    panelCiphers->addElement(std::move(elementFactory->createButton("Encrypt", CommandCipherEncrypt())));
    
    auto panelInputText{ elementFactory->createPanel("Input Text") };
    panelInputText->addElement(std::move(elementFactory->createButton("Load File", CommandOpenLoadWindow(std::move(*m_GUI)))));
    panelInputText->addElement(std::move(elementFactory->createTextbox("Input Text", *m_InputText)));

    auto panelOutputText{ elementFactory->createPanel("Output Text") };
    panelOutputText->addElement(std::move(elementFactory->createButton("Save File", CommandOpenSaveWindow(std::move(*m_GUI)))));
    panelOutputText->addElement(std::move(elementFactory->createTextbox("Output Text", *m_OutputText)));


    m_GUI->addElement(std::move(panelCiphers));
    m_GUI->addElement(std::move(panelInputText));
    m_GUI->addElement(std::move(panelOutputText));
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

const std::string& Cryptography::getOutputText()
{
    return *m_OutputText;
}

void Cryptography::registerCipher(Cipher* cipher)
{
    m_Ciphers.emplace_back(std::move(cipher));
}
