#pragma once

#include <memory>
#include <vlGraphics/Rendering.hpp>
#include <vlGraphics/RenderingTree.hpp>
#include <vlGraphics/SceneManagerActorKdTree.hpp>
#include <vlGraphics/TrackballManipulator.hpp>

#include "gui/Menu.hpp"

#include "camera/DoubleCamera.hpp"
#include "scene/City.hpp"
#include "utils/DefaultUiEventListener.hpp"
#include "utils/OcclusionStatistics.hpp"
#include "utils/VisualizationState.hpp"
#include "utils/vl/MakeRef.hpp"
#include "ViewType.hpp"

namespace ocv
{
class VisualizationView : public DefaultUiEventListener
{
public:
    VisualizationView(std::shared_ptr<Window>,
                      std::shared_ptr<DoubleCamera>,
                      std::shared_ptr<PlayerVisualizationState>,
                      std::shared_ptr<ObservatorVisualizationState>,
                      std::shared_ptr<OcclusionStatistics>,
                      std::shared_ptr<bool> preview,
                      vl::Renderer* player,
                      vl::Renderer* observator);

    void hideOrShowSecondView();
    void enableDisableOcclusionCulling();
    void enableDisableRenderingWhatPlayerRender();
    void enableDisableWireModeForOcluded();
    void toggleObservatorAABBDraw();
    void togglePlayerAABBDraw();
    void toggleActiveView();
    void enterExitEditorMode();
    void switchBetweenMainAndSecondView();
    void toggleMenu();
    void closeApplication();

private:
    void initEvent() override;
    void resizeEvent(int width, int height) override;
    void updateEvent() override;

    void switchMainSecondView();
    void attachRenderings();
    void attachSceneManager();
    void attachRenderer(vl::Renderer* player, vl::Renderer* observator);
    void attachCameras();

    void resizeMainView();
    void resizeSecondView();
    void resizeViews();
    void resizeView(vl::Rendering*, int x, int y, int width, int height);
    void updateFramebufferSize(int width, int height);

    void prepareMainView();
    void preparePreviewView();

    vl::ref<vl::SceneManagerActorKdTree> scenePlayerGuiActorTree =
        make_ref<vl::SceneManagerActorKdTree>();

    vl::ref<vl::SceneManagerActorKdTree> sceneObservatorGuiActorTree =
        make_ref<vl::SceneManagerActorKdTree>();

    vl::ref<vl::RenderingTree> mRenderingTree = make_ref<vl::RenderingTree>();

    vl::ref<vl::Rendering> playerRendering = make_ref<vl::Rendering>();
    vl::ref<vl::Rendering> observatorRendering = make_ref<vl::Rendering>();

    vl::Rendering* mainView{playerRendering.get()};
    vl::Rendering* previewView{observatorRendering.get()};

    std::shared_ptr<ViewType> currentMainView{
        std::make_shared<ViewType>(ViewType::Player)};

    vl::ref<vl::Framebuffer> framebuffer;
    std::shared_ptr<DoubleCamera> doubleCamera;
    City city;

    std::shared_ptr<PlayerVisualizationState> playerVisualizationState;
    std::shared_ptr<ObservatorVisualizationState> observatorVisualizationState;
    std::shared_ptr<bool> previewEnabled;
    std::shared_ptr<menu> infoMenu;

    int currentFramebufferWidth;
    int currentFramebufferHeight;
};

std::unique_ptr<VisualizationView>
    createVisualizationView(std::shared_ptr<Window>,
                            std::shared_ptr<DoubleCamera>);

}
