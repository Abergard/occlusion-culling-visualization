#include "Player.hpp"

#include <vlCore/Colors.hpp>
#include <vlCore/Time.hpp>

#include <sstream>

#include "utils/vl/Log.hpp"

namespace ocv
{
Player::Player(vl::ref<vl::Camera> c)
{
    setCamera(c.get());
    camera()->setFarPlane(10000.0f);

    auto eye = vl::vec3(0, 0, 0);            // camera position
    auto center = vl::vec3(400, 10.0f, 400); // point the camera is looking at
    auto up = vl::vec3(0, 1, 0);             // up direction
    auto viewMat = vl::mat4::getLookAt(eye, center, up);

    camera()->setViewMatrix(viewMat);
    camera()->viewport()->setClearColor(vl::vec4{0.529f, 0.808f, 0.922f, 1});

    mPosition = vl::vec3{0, 10, 0};
}

void Player::enableEvent(bool enabled)
{
    Debug(std::string("Player enable Event: ") + std::to_string(enabled));
    vl::GhostCameraManipulator::enableEvent(enabled);
    if (enabled)
        mLastTime = vl::Time::currentTime();
}

void Player::updateMouse()
{
    int cx = (int)camera()->viewport()->center().x();
    int cy = openglContext()->framebuffer()->height() -
             camera()->viewport()->height() / 2 - camera()->viewport()->y();

    openglContext()->setMousePosition(cx, cy);
}

void Player::mouseMoveEvent(int x, int y)
{
    vl::GhostCameraManipulator::mouseMoveEvent(x, y);
}

void Player::updateEvent()
{
    if (camera() == NULL)
        return;

    if (mLastTime == 0)
    {
        mLastTime = vl::Time::currentTime();
        return;
    }

    if (openglContext()->isKeyPressed(vl::Key_Shift))
    {
        mMovementSpeed = sprintSpeed;
    }
    else if (openglContext()->isKeyPressed(vl::Key_Ctrl))
    {
        mMovementSpeed = walkingSpeed;
    }
    else
    {
        mMovementSpeed = runningSpeed;
    }

    vl::real dt = vl::Time::currentTime() - mLastTime;

    mLastTime = vl::Time::currentTime();

    vl::mat4 m = vl::mat4::getTranslation(mPosition);
    m *= vl::mat4::getRotation(
        mYDegrees, vl::vec3(0, 1, 0), mXDegrees, vl::vec3(1, 0, 0));

    camera()->setModelingMatrix(m);
    camera()->boundTransform()->setLocalMatrix(camera()->modelingMatrix());

    vl::vec3 direction;

    if (openglContext()->isKeyPressed(mKeysLeft[0]))
        direction.x() = -1;

    if (openglContext()->isKeyPressed(mKeysRight[0]))
        direction.x() = +1;

    if (openglContext()->isKeyPressed(mKeysBackward[0]))
        direction.z() = -1;

    if (openglContext()->isKeyPressed(mKeysForward[0]))
        direction.z() = +1;

    vl::vec3 dir;
    dir += camera()->modelingMatrix().getX() * direction.x();
    dir += camera()->modelingMatrix().getY() * direction.y();
    dir -= camera()->modelingMatrix().getZ() * direction.z();
    dir.normalize();
    dir.y() = 0;
    mPosition += dir * (vl::real)(dt * mMovementSpeed);
}
}
