#pragma once

#include "Window.hpp"

#include <vlGLFW/GLFWWindow.hpp>

namespace ocv
{
class GlfwWindow : public Window
{
public:
    GlfwWindow(const vl::String& windowName,
                const int widthScreen,
                const int heightScreen);

    void addEventListener(vl::UIEventListener*) override;
    void show() override;
    int messageLoop() override;
    void setMouseVisible(bool) override;

    vl::Framebuffer* framebuffer() override;
    const vl::Framebuffer* framebuffer() const override;

private:
    vl::ref<vlGLFW::GLFWWindow> window;
};
}
