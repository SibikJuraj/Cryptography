#include <iostream>

#include "Application.h"

#include <Ciphers/Caesar.h>
#include <Ciphers/Affine.h>
#include <Ciphers/Viegener.h>
#include <Ciphers/Hill.h>
#include <Ciphers/Stream.h>
#include <Ciphers/RSA.h>
#include <Text/TextLoader.h>
#include <PwdAuth.h>

#include <GUI/ImGUI/ImGUI.h>
#include <GUI/ImGUI/ImGUIElements.h>
//#include <GUI/ImGUIElementsFactory.h>
//#include <GUI/ImGUIElements.h>

Application::Application() : 
    m_GUI{ std::make_unique<ImGUI>(1600, 900) }, m_Ciphers{}
{
    registerCipher(Caesar());
    registerCipher(Affine());
    registerCipher(Viegener());
    registerCipher(Stream());
    registerCipher(Hill());
    registerCipher(RSA());

    ImGUIPanel panelCiphers{ "Ciphers" };
    std::vector<const char*> cipherNames{ "Caesar" };
   /* panelCiphers.addElement(ImGUIComboboxCipher("Cipher", cipherNames));
    panelCiphers.addElement(ImGUIButton("Decrypt", CommandCipherDecrypt()));
    panelCiphers.addElement(ImGUIButton("Encrypt", CommandCipherEncrypt()));*/
    //m_GUI->addElement(std::make_unique<ImGUIPanel>(panelCiphers));
    //TODO 
    //VYTVOR GUI JAK MA VYZERAT + NAPLN CO MA EXECUTOVAT KOMANDY ... CO SA MA VYKONAVAT
}

void Application::run()
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
        m_GUI->render();
}

void Application::registerCipher(Cipher& cipher)
{
    m_Ciphers.push_back(std::make_unique<Cipher>(cipher));
}
