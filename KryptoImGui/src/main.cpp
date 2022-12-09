#include <windows.h>
#include <debugapi.h>
#include <crtdbg.h>

#include <memory>
#include <string>
#include <iostream>
#include <sstream>

#include <Text/TextLoader.h>
#include <Ciphers/Stream.h>
#include <Ciphers/Viegener.h>
#include <Ciphers/Hill.h>
#include <PwdAuth.h>
#include <Ciphers/RSA.h>

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    /*auto textVigenere{ TextLoader::loadText("texts/vigenere/text1_enc.txt") };
    auto decryptedTextVigenere{ Viegener().decrypt(textVigenere) };
    TextLoader::saveText("texts/vigenere/decoded/text1_dec.txt", decryptedTextVigenere);

    auto textStream{ TextLoader::loadText("texts/stream/text1_enc.txt") };
    auto decryptedTextStream{ Stream().decrypt(textStream) };
    TextLoader::saveText("texts/stream/decoded/text1_dec.txt", decryptedTextStream); */
    
    /*auto textHill{ TextLoader::loadText("texts/hill/text3_enc.txt") };
    auto decryptedTextHill{ Hill({ 3, 7, 20, 17, 24, 17, 0, 9, 0 }).decrypt(textHill) };
    TextLoader::saveText("texts/hill/decoded/text3_dec.txt", decryptedTextHill);*/

    /*TextLoader::saveText("texts/md5/decoded/shadow4_pwd.txt", 
        PwdAuth::decrypt(TextLoader::loadText("texts/md5/shadow4.txt")));*/

    /*RSA rsa;
    rsa.decrypt("");*/

    return 0;
}
