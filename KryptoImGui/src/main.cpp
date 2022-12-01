#include <windows.h>
#include <debugapi.h>
#include <iostream>
#include <crtdbg.h>

#include <Text/TextLoader.h>
#include <Text/Class Text/Text.h>
#include <Ciphers/StreamGen.h>
#include <Ciphers/Viegener.h>

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    auto text{ TextLoader::loadFile("texts/vigenere/text1_enc.txt") };
    auto viegener{ Viegener() };
    auto decryptedText{ viegener.decrypt(text) };

    TextLoader::saveText("texts/vigenere/text1_dec.txt",decryptedText);

    //StreamGen::init();

    return 0;
}
