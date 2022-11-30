#include <windows.h>
#include <debugapi.h>
#include <iostream>
#include <crtdbg.h>

#include <Text/TextLoader.h>
#include <Text/Class Text/Text.h>
#include <Ciphers/Class Stream/StreamGen.h>

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    //Application::getInstance().run();
    auto text{ TextLoader::loadFile("texts/vigenere/text1_enc.txt") };
    //std::cout << text->textWithSpaces() << '\n';

    StreamGen::init();

    return 0;
}
