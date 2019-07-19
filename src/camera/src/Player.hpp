#pragma once

#include <vlGraphics/GhostCameraManipulator.hpp>

namespace ocv
{
class Player : public vl::GhostCameraManipulator
{
public:
    Player(vl::ref<vl::Camera>);

    void updateEvent() override;
    void enableEvent(bool enabled) override;
    void mouseMoveEvent(int x, int y) override;

    void updateMouse();

private:
    const float walkingSpeed{8.0f};
    const float runningSpeed{22.0f};
    const float sprintSpeed{55.0f};
};
}
