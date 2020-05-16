#include "DoubleCamera.hpp"

#include <vlCore/Colors.hpp>
#include <vlCore/Matrix4.hpp>
#include <vlCore/Object.hpp>
#include <vlGraphics/Camera.hpp>
#include <vlGraphics/OpenGLContext.hpp>
#include <vlGraphics/Rendering.hpp>

#include "Observator.hpp"
#include "Player.hpp"
#include "utils/vl/Log.hpp"
#include "utils/vl/MakeRef.hpp"
#include "window/Window.hpp"

namespace ocv
{

struct GhostCamerasHolder
{
    vl::ref<Player> player;
    vl::ref<Observator> observator;
};

namespace
{
std::unique_ptr<GhostCamerasHolder> initializeCameras()
{
    auto cameras = std::make_unique<GhostCamerasHolder>();
    cameras->player = make_ref<Player>(make_ref<vl::Camera>());
    cameras->observator = make_ref<Observator>(make_ref<vl::Camera>());
    return cameras;
}
}

DoubleCamera::DoubleCamera(Window& window)
    : cameras{initializeCameras()}, window{window}
{
    Debug("Construct double camera");
    enableDisableCameras();
}

DoubleCamera::~DoubleCamera()
{
    
}

void DoubleCamera::addedListenerEvent(vl::OpenGLContext* oglContext)
{
    oglContext->addEventListener(cameras->player.get());
    oglContext->addEventListener(cameras->observator.get());
}

void DoubleCamera::removedListenerEvent(vl::OpenGLContext* oglContext)
{
    oglContext->removeEventListener(cameras->player.get());
    oglContext->removeEventListener(cameras->observator.get());
}

void DoubleCamera::enableDisableCameras()
{
    areCamerasDisabled = !areCamerasDisabled;
    if (areCamerasDisabled)
    {
        window.setMouseVisible(true);
        cameras->player->setEnabled(false);
        cameras->observator->setEnabled(false);
    }
    else
    {
        window.setMouseVisible(false);
        cameras->player->setEnabled(isFirstEnabled);
        cameras->observator->setEnabled(isSecondEnabled);
    }
}

void DoubleCamera::switchActiveCamera()
{
    Debug("switch cameras");
    if (!areCamerasDisabled)
    {
        cameras->player->setEnabled(!cameras->player->isEnabled());
        cameras->observator->setEnabled(!cameras->observator->isEnabled());
        Debug("switch cameras done");
    }
}

CameraType DoubleCamera::activeCamera()
{
    if (areCamerasDisabled)
    {
        return CameraType::Editor;
    }

    if (cameras->player->isEnabled())
    {
        return CameraType::Player;
    }

    return CameraType::Observator;
}

vl::vec3 DoubleCamera::getPosition()
{
    return cameras->player->camera()->modelingMatrix().getT();
}

vl::Camera* DoubleCamera::playerCamera()
{
    return cameras->player->camera();
}

vl::Camera* DoubleCamera::observatorCamera()
{
    return cameras->observator->camera();
}

void DoubleCamera::updateMouse()
{
    switch (activeCamera())
    {
    case CameraType::Player:
        cameras->player->updateMouse();
        break;

    case CameraType::Observator:
        cameras->observator->updateMouse();
        break;
    }
}
}
