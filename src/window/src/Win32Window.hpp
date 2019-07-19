#pragma once

#include "Window.hpp"

#include <vlWin32/Win32Window.hpp>

namespace ocv
{
class Win32Window : public Window
{
public:
    Win32Window(const vl::String& windowName,
                const int widthScreen,
                const int heightScreen);

    void addEventListener(vl::UIEventListener*) override;
    void show() override;
    int messageLoop() override;
    void setMouseVisible(bool) override;

    vl::Framebuffer* framebuffer() override;
    const vl::Framebuffer* framebuffer() const override;

private:
    vl::ref<vlWin32::Win32Window> window;
};
}
