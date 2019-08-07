#pragma once

#include <memory>
#include <string>

namespace vl
{
class UIEventListener;
class Framebuffer;
}

namespace ocv
{
class Window
{
public:
    ~Window() = default;

    virtual void addEventListener(vl::UIEventListener*) = 0;
    virtual void show() = 0;
    virtual int messageLoop() = 0;

    virtual vl::Framebuffer*
        framebuffer() = 0; // TODO: create own type for framebuffer
    virtual const vl::Framebuffer* framebuffer() const = 0;
    virtual void setMouseVisible(bool) = 0;
};

// std::unique_ptr<Window>
//     createWin32Window(std::string title, int width, int height);

std::unique_ptr<Window>
    createGlfwWindow(std::string title, int width, int height);
}
