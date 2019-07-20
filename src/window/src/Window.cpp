#include "Window.hpp"

#include "Win32Window.hpp"

namespace ocv
{
std::unique_ptr<Window>
    createWin32Window(std::string title, const int width, const int height)
{
    return std::make_unique<Win32Window>(std::move(title), width, height);
}
}
