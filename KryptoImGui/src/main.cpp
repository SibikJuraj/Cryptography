#include <windows.h>
#include <debugapi.h>
#include <iostream>
#include <crtdbg.h>

#include <Text/TextLoader.h>
#include <Ciphers/Stream.h>
#include <Ciphers/Viegener.h>

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    auto textVigenere{ TextLoader::loadText("texts/vigenere/text1_enc.txt") };
    auto textStream{ TextLoader::loadText("texts/stream/text2_enc.txt") };

    auto decryptedTextVigenere{ Viegener().decrypt(textVigenere) };
    auto decryptedTextStream{ Stream().decrypt(textStream) };

    TextLoader::saveText("texts/vigenere/decoded/text1_dec.txt", decryptedTextVigenere);
    TextLoader::saveText("texts/stream/decoded/text2_dec.txt", decryptedTextStream);

    return 0;
}
