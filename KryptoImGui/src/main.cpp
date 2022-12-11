//#include <windows.h>
//#include <debugapi.h>
//#include <crtdbg.h>

#include <Class Cryptography/Cryptography.h>
int main()
{
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Cryptography::getInstance().run();

    return 0;
}
