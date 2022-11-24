#include <windows.h>
#include "Engine/Core/Application.h"
#include <debugapi.h>

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Application::getInstance().run();
    
    return 0;
}
