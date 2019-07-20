#include "Win32Window.hpp"

#include "utils/vl/Log.hpp"
#include "utils/vl/MakeRef.hpp"

namespace ocv
{
namespace
{
vl::OpenGLContextFormat prepareContextFormat()
{
    vl::OpenGLContextFormat format;
    format.setDoubleBuffer(true);
    format.setRGBABits(8, 8, 8, 8);
    format.setDepthBufferBits(24);
    format.setStencilBufferBits(8);
    format.setFullscreen(false);
    format.setMultisampleSamples(16);
    format.setMultisample(false);
    format.setVSync(false);
    return format;
}
}

Win32Window::Win32Window(const vl::String& windowName,
                         const int widthScreen,
                         const int heightScreen)
    : window{make_ref<vlWin32::Win32Window>()}
{
    Debug("Preparing main window");
    constexpr auto x = 0, y = 0;
    window->initWin32GLWindow(NULL,
                              NULL,
                              windowName,
                              prepareContextFormat(),
                              x,
                              y,
                              widthScreen,
                              heightScreen);
}

void Win32Window::addEventListener(vl::UIEventListener* listener)
{
    window->addEventListener(listener);
}

void Win32Window::show()
{
    window->show();
}

int Win32Window::messageLoop()
{
    return vlWin32::messageLoop();
}

void Win32Window::setMouseVisible(bool isVisible)
{
    window->setMouseVisible(isVisible);
}

vl::Framebuffer* Win32Window::framebuffer()
{
    return window->framebuffer();
}

const vl::Framebuffer* Win32Window::framebuffer() const
{
    return window->framebuffer();
}
}
