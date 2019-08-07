#include "GlfwWindow.hpp"

#include "utils/vl/Log.hpp"
#include "utils/vl/MakeRef.hpp"

namespace ocv
{
namespace
{
vl::OpenGLContextFormat prepareContextFormat()
{
    vl::OpenGLContextFormat format{};
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

static void error_callback(int /*error*/, const char* description)
{
    fputs(description, stderr);
}
}

GlfwWindow::GlfwWindow(const vl::String& windowName,
                       const int widthScreen,
                       const int heightScreen)
    : window{make_ref<vlGLFW::GLFWWindow>()}
{
    Debug("Preparing main window");

    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    constexpr auto x = 0, y = 0;
    window->initGLFWWindow(
        windowName, prepareContextFormat(), widthScreen, heightScreen);
}

void GlfwWindow::addEventListener(vl::UIEventListener* listener)
{
    window->addEventListener(listener);
}

void GlfwWindow::show()
{
    window->show();
}

int GlfwWindow::messageLoop()
{
    while (window->windows().size())
    {
        if (window->continuousUpdate())
        {
            window->update();
        }
        glfwPollEvents();
    }
    return 0;
}

void GlfwWindow::setMouseVisible(bool isVisible)
{
    window->setMouseVisible(isVisible);
}

vl::Framebuffer* GlfwWindow::framebuffer()
{
    return window->framebuffer();
}

const vl::Framebuffer* GlfwWindow::framebuffer() const
{
    return window->framebuffer();
}
}
