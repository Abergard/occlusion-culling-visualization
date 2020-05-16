#pragma once
#include <memory>

#include <vlCore/Vector3.hpp>

#include "CameraType.hpp"
#include "utils/DefaultUiEventListener.hpp"

namespace vl
{
class Camera;
class OpenGLContext;
}

namespace ocv
{
struct GhostCamerasHolder;
class Window;
class DoubleCamera : public DefaultUiEventListener
{
public:
    DoubleCamera(Window& window);
    ~DoubleCamera();

    void addedListenerEvent(vl::OpenGLContext*) override;
    void removedListenerEvent(vl::OpenGLContext*) override;

    void enableDisableCameras();
    void switchActiveCamera();
    vl::vec3 getPosition();
    vl::Camera* playerCamera();
    vl::Camera* observatorCamera();
    void updateMouse();
    CameraType activeCamera();

private:
    std::unique_ptr<GhostCamerasHolder> cameras;
    Window& window;

    bool areCamerasDisabled{true};

    bool isFirstEnabled{true};
    bool isSecondEnabled{false};
};
}
