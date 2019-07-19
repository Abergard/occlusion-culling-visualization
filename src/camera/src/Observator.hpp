#pragma once

#include <vlCore/Transform.hpp>
#include <vlGraphics/GhostCameraManipulator.hpp>

namespace ocv
{
class Observator : public vl::GhostCameraManipulator
{
public:
    Observator(vl::ref<vl::Camera>);

    void enableEvent(bool enabled) override;
    void updateEvent() override;
    void updateMouse();
};
}
