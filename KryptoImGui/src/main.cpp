#include <windows.h>
#include <debugapi.h>
#include <crtdbg.h>

#include <Class Application/Application.h>

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Application::getInstance().run();

    return 0;
}
