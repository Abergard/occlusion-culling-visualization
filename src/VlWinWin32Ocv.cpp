#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include <cstdlib>
#include <shellapi.h>
#include <string>

#include "VlWin32Ocv.hpp"

ScreenSize getScreenSize(PWSTR pCmdLine)
{
    int argc{0};
    const auto argv = CommandLineToArgvW(pCmdLine, &argc);

    if (argc != 2)
        return getFullScreenSize();

    const auto mainScreen{ScreenSize{_wtoi(argv[0]), _wtoi(argv[1])}};
    if (mainScreen.width == 0 || mainScreen.height == 0)
    {
        MessageBox(nullptr,
                   "Can not parse screen size from args!",
                   "Invalid screen size!",
                   MB_OK | MB_ICONERROR);
        exit(-1);
    }
    return mainScreen;
}

int WINAPI wWinMain(HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    PWSTR pCmdLine,
                    int nCmdShow)
{
    return start(getScreenSize(pCmdLine));
}
