#include "VisualizationView.hpp"

#include <vlCore/Colors.hpp>
#include <vlCore/Log.hpp>
#include <vlCore/Say.hpp>
#include <vlCore/Time.hpp>
#include <vlCore/VisualizationLibrary.hpp>
#include <vlGraphics/ActorTreeAbstract.hpp>
#include <vlGraphics/OpenGLContext.hpp>
#include <vlGraphics/RenderQueue.hpp>
#include <vlGraphics/RenderQueueSorter.hpp>
#include <vlGraphics/Rendering.hpp>
#include <vlGraphics/RenderingTree.hpp>
#include <vlGraphics/SceneManager.hpp>
#include <vlGraphics/SceneManagerActorKdTree.hpp>
#include <vlGraphics/SceneManagerActorTree.hpp>
#include <vlGraphics/SceneManagerBVH.hpp>
#include <vlGraphics/TrackballManipulator.hpp>

#include "renderer/GuiRenderer.hpp"
#include "renderer/ObservatorRenderer.hpp"
#include "renderer/PlayerRenderer.hpp"
#include "utils/vl/Log.hpp"
#include "utils/vl/MakeRef.hpp"
#include "window/Window.hpp"

namespace ocv
{
namespace
{
bool operator==(const CameraType camera, const ViewType mainView)
{
    return camera == CameraType::Player && mainView == ViewType::Player ||
           camera == CameraType::Observator &&
               mainView == ViewType::Observator;
}

bool operator==(const ViewType mainView, const CameraType camera)
{
    return camera == mainView;
}

bool operator!=(const CameraType camera, const ViewType mainView)
{
    return !(camera == mainView);
}
bool operator!=(const ViewType mainView, const CameraType camera)
{
    return camera != mainView;
}
}

VisualizationView::VisualizationView(
    Window& window,
    DoubleCamera& camera,
    std::shared_ptr<PlayerVisualizationState> playerState,
    std::shared_ptr<ObservatorVisualizationState> observatorState,
    std::shared_ptr<OcclusionStatistics> statistics,
    std::shared_ptr<bool> preview,
    vl::Renderer* player,
    vl::Renderer* observator)
    : framebuffer{window.framebuffer()},
      doubleCamera{camera},
      city{doubleCamera},
      playerVisualizationState{std::move(playerState)},
      observatorVisualizationState{std::move(observatorState)},
      previewEnabled{std::move(preview)},
      infoMenu{createInformationMenu(framebuffer->openglContext(),
                                     statistics,
                                     doubleCamera,
                                     playerVisualizationState,
                                     observatorVisualizationState,
                                     previewEnabled,
                                     currentMainView,
                                     scenePlayerGuiActorTree->tree(),
                                     sceneObservatorGuiActorTree->tree())},
      currentFramebufferWidth{framebuffer->width()},
      currentFramebufferHeight{framebuffer->height()}
{
    Trace();

    if (previewEnabled)
    {
        Debug("view enabled");
    }
    else
    {
        Debug("view disabled");
    }

    auto sorter = make_ref<vl::RenderQueueSorterOcclusion>();
    playerRendering->setRenderQueueSorter(sorter.get());

    attachSceneManager();
    attachRenderer(player, observator);
    attachCameras();

    attachRenderings();

    auto effect = make_ref<vl::Effect>();
    auto shader = effect->shader();
    shader->enable(vl::EN_DEPTH_TEST);
    shader->enable(vl::EN_LINE_SMOOTH);
    shader->enable(vl::EN_BLEND);
    shader->enable(vl::EN_POLYGON_OFFSET_LINE);
    shader->gocPolygonMode()->set(vl::PM_LINE, vl::PM_LINE);
    shader->gocColor()->setValue(vl::lightgreen);
    shader->setRenderState(shader->getMaterial());
    shader->setRenderState(shader->getLight(0), 0);
    shader->gocPolygonOffset()->set(-1.0f, -1.0f);

    observatorRendering->effectOverrideMask()[0x00000001] = effect;
}

void VisualizationView::initEvent()
{
    if (!vl::Has_Occlusion_Query)
    {
        Error("No support to hardware occlusion culling found!\n");
        vl::Time::sleep(2000);
        exit(1);
    }

    Debug("need to transform");
    playerRendering->transform()->addChild(
        doubleCamera.playerCamera()->boundTransform());
}

void VisualizationView::attachRenderings()
{
    Trace();
    if (*currentMainView == ViewType::Observator && !*previewEnabled)
    {
        // FIXME: Observator view uses information generated during player view
        // rendering that why we need to push player rendering here.
        mRenderingTree->subRenderings()->push_back(playerRendering.get());
    }
    prepareMainView();
    preparePreviewView();
}

void VisualizationView::prepareMainView()
{
    mRenderingTree->subRenderings()->push_back(mainView);
    resizeView(
        mainView, 0, 0, currentFramebufferWidth, currentFramebufferHeight);
}

void VisualizationView::preparePreviewView()
{
    if (*previewEnabled)
    {
        mRenderingTree->subRenderings()->push_back(previewView);
    }

    int const secondViewWidth = currentFramebufferWidth / 3;
    int const beginOfSecondViewX = currentFramebufferWidth - secondViewWidth;

    int const secondViewHeight = currentFramebufferHeight / 3;
    int const beginOfSecondViewY = currentFramebufferHeight - secondViewHeight;

    resizeView(previewView,
               beginOfSecondViewX,
               beginOfSecondViewY,
               secondViewWidth,
               secondViewHeight);
}

void VisualizationView::attachCameras()
{
    Trace();
    observatorRendering->setCamera(doubleCamera.observatorCamera());
    playerRendering->setCamera(doubleCamera.playerCamera());
}

void VisualizationView::switchMainSecondView()
{
    if (*currentMainView == ViewType::Player)
    {
        *currentMainView = ViewType::Observator;
        mainView = observatorRendering.get();
        previewView = playerRendering.get();
    }
    else
    {
        *currentMainView = ViewType::Player;
        mainView = playerRendering.get();
        previewView = observatorRendering.get();
    }

    mRenderingTree->subRenderings()->clear();
    attachRenderings();
}

void VisualizationView::hideOrShowSecondView()
{
    Trace();

    if (*previewEnabled)
    {
        *previewEnabled = false;
        mRenderingTree->subRenderings()->pop_back();
    }
    else
    {
        *previewEnabled = true;
        mRenderingTree->subRenderings()->push_back(previewView);
    }
}

void VisualizationView::attachSceneManager()
{
    Trace();
    observatorRendering->sceneManagers()->push_back(city.sceneManager());
    observatorRendering->sceneManagers()->push_back(
        sceneObservatorGuiActorTree.get());
    playerRendering->sceneManagers()->push_back(scenePlayerGuiActorTree.get());
    playerRendering->sceneManagers()->push_back(city.sceneManager());
}

void VisualizationView::attachRenderer(vl::Renderer* player,
                                       vl::Renderer* observator)
{
    Trace();

    auto guiRenderer = make_ref<GuiRenderer>();
    guiRenderer->setFramebuffer(framebuffer.get());

    observatorRendering->setRenderer(observator);
    observatorRendering->renderers().push_back(guiRenderer.get());

    playerRendering->setRenderer(player);
    playerRendering->renderers().push_back(guiRenderer.get());

    observatorRendering->renderer()->setFramebuffer(framebuffer.get());
    playerRendering->renderer()->setFramebuffer(framebuffer.get());
}

void VisualizationView::updateEvent()
{
    infoMenu->render();

    mRenderingTree->setFrameClock(vl::Time::currentTime());
    mRenderingTree->render();

    if (framebuffer->openglContext()->hasDoubleBuffer())
    {
        framebuffer->openglContext()->swapBuffers();
    }

    VL_CHECK_OGL();
}

void VisualizationView::resizeEvent(int windowWidth, int windowHeight)
{
    updateFramebufferSize(windowWidth, windowHeight);
    resizeViews();
}

void VisualizationView::updateFramebufferSize(int width, int height)
{
    currentFramebufferWidth = width;
    currentFramebufferHeight = height;
    framebuffer->setWidth(width);
    framebuffer->setHeight(height);
}

void VisualizationView::resizeViews()
{
    resizeMainView();
    resizeSecondView();
}

void VisualizationView::resizeMainView()
{
    resizeView(
        mainView, 0, 0, currentFramebufferWidth, currentFramebufferHeight);
}

void VisualizationView::resizeSecondView()
{
    int secondViewWidth = currentFramebufferWidth / 3;
    int beginOfSecondViewX = currentFramebufferWidth - secondViewWidth;

    int secondViewHeight = currentFramebufferHeight / 3;
    int beginOfSecondViewY = currentFramebufferHeight - secondViewHeight;

    resizeView(previewView,
               beginOfSecondViewX,
               beginOfSecondViewY,
               secondViewWidth,
               secondViewHeight);
}

void VisualizationView::resizeView(vl::Rendering* view,
                                   int x,
                                   int y,
                                   int width,
                                   int height)
{
    view->camera()->viewport()->set(x, y, width, height);
    view->camera()->setProjectionPerspective();
}

void VisualizationView::enableDisableOcclusionCulling()
{
    Trace();

    playerVisualizationState->occlusionCullingState =
        !playerVisualizationState->occlusionCullingState;
}

void VisualizationView::enableDisableRenderingWhatPlayerRender()
{
    Trace();

    observatorVisualizationState->observatorState =
        !observatorVisualizationState->observatorState;
}

void VisualizationView::enableDisableWireModeForOcluded()
{
    Trace();

    observatorVisualizationState->wireState =
        !observatorVisualizationState->wireState;
}

void VisualizationView::toggleObservatorAABBDraw()
{
    observatorVisualizationState->aabbState =
        !observatorVisualizationState->aabbState;
}

void VisualizationView::togglePlayerAABBDraw()
{
    playerVisualizationState->aabbState = !playerVisualizationState->aabbState;
}

void VisualizationView::toggleActiveView()
{
    if (*previewEnabled || *currentMainView == ViewType::Observator)
    {
        doubleCamera.switchActiveCamera();
    }
}

void VisualizationView::enterExitEditorMode()
{
    Trace();
    doubleCamera.enableDisableCameras();
}

void VisualizationView::switchBetweenMainAndSecondView()
{
    Trace();
    switchMainSecondView();
    if (!*previewEnabled && *currentMainView != doubleCamera.activeCamera())
    {
        doubleCamera.switchActiveCamera();
    }
    doubleCamera.updateMouse();
}

void VisualizationView::toggleMenu()
{
    infoMenu->showOrHide();
}

void VisualizationView::closeApplication()
{
    framebuffer->openglContext()->quitApplication();
}

std::unique_ptr<VisualizationView>
    createVisualizationView(Window& window,
                            DoubleCamera& camera)
{
    auto playerVisualizationState =
        std::make_shared<ocv::PlayerVisualizationState>();
    auto observatorVisualizationState =
        std::make_shared<ocv::ObservatorVisualizationState>();
    auto statistics = std::make_shared<ocv::OcclusionStatistics>();
    auto notOccludedQueue = std::make_shared<vl::RenderQueue>();
    auto player = ocv::make_ref<ocv::PlayerRenderer>(
        notOccludedQueue, playerVisualizationState, statistics);
    auto observator = ocv::make_ref<ocv::ObservatorRenderer>(
        notOccludedQueue, observatorVisualizationState);

    std::shared_ptr<bool> previewEnabled{std::make_shared<bool>(false)};

    return std::make_unique<ocv::VisualizationView>(
        window,
        camera,
        playerVisualizationState,
        observatorVisualizationState,
        statistics,
        std::move(previewEnabled),
        player.get(),
        observator.get());
}
}
