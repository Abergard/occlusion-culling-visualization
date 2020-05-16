#include "Observator.hpp"

#include <vlCore/Colors.hpp>
#include <vlCore/Time.hpp>

#include "utils/vl/Log.hpp"
#include "utils/vl/MakeRef.hpp"

namespace ocv
{
Observator::Observator(vl::ref<vl::Camera> c)
{
    setCamera(c.get());
    camera()->setFarPlane(10000.0f);

    const vl::vec3 startupPosition{200, 300, 60};
    const vl::vec3 lookAtPoint{0, 0, 0};
    const vl::vec3 upDirection{0, 1, 0};
    const auto sunColor = vl::vec4{0.529f, 0.808f, 0.922f, 1};
    const auto viewMat =
        vl::mat4::getLookAt(startupPosition, lookAtPoint, upDirection);
    camera()->setViewMatrix(viewMat);
    camera()->viewport()->setClearColor(sunColor);
    camera()->applyViewMatrix();
    camera()->applyProjMatrix();

    mMovementSpeed = 1.0f;
}

void Observator::enableEvent(bool enabled)
{
    Debug(std::string("Observator enable Event: ") + std::to_string(enabled));
    vl::GhostCameraManipulator::enableEvent(enabled);
    if (enabled)
        mLastTime = vl::Time::currentTime();
}

void Observator::updateEvent()
{
    vl::GhostCameraManipulator::updateEvent();
}

void Observator::updateMouse()
{
    int cx = (int)camera()->viewport()->center().x();
    int cy = openglContext()->framebuffer()->height() -
             camera()->viewport()->height() / 2 - camera()->viewport()->y();

    openglContext()->setMousePosition(cx, cy);
}
}
