#pragma once

#include <vlGraphics/UIEventListener.hpp>

namespace ocv
{
class DefaultUiEventListener : public vl::UIEventListener
{
public:
    void initEvent() override{};
    void destroyEvent() override{};
    void updateEvent() override{};
    void enableEvent(bool /*enabled*/) override{};
    void addedListenerEvent(vl::OpenGLContext*) override{};
    void removedListenerEvent(vl::OpenGLContext*) override{};
    void mouseMoveEvent(int /*x*/, int /*y*/) override{};
    void mouseUpEvent(vl::EMouseButton, int /*x*/, int /*y*/) override{};
    void mouseDownEvent(vl::EMouseButton, int /*x*/, int /*y*/) override{};
    void mouseWheelEvent(int /*n*/) override{};
    void keyPressEvent(unsigned short /*unicode_ch*/, vl::EKey) override{};
    void keyReleaseEvent(unsigned short /*unicode_ch*/, vl::EKey) override{};
    void resizeEvent(int /*x*/, int /*y*/) override{};
    void fileDroppedEvent(const std::vector<vl::String>& /*files*/) override{};
    void visibilityEvent(bool /*visible*/) override{};
};
}
