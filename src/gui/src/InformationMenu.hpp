#pragma once

#include <memory>
#include <string>

#include <vlGraphics/ActorTreeAbstract.hpp>
#include <vlGraphics/Text.hpp>

#include "camera/DoubleCamera.hpp"
#include "Menu.hpp"
#include "utils/FpsCounter.hpp"
#include "utils/OcclusionStatistics.hpp"
#include "utils/VisualizationState.hpp"
#include "view/ViewType.hpp"

namespace ocv
{
class InformationMenu : public menu
{
public:
    InformationMenu(vl::OpenGLContext* context,
                    std::shared_ptr<OcclusionStatistics>,
                    std::shared_ptr<DoubleCamera>,
                    std::shared_ptr<PlayerVisualizationState>,
                    std::shared_ptr<ObservatorVisualizationState>,
                    std::shared_ptr<bool> preview,
                    std::shared_ptr<ViewType> view_type,
                    vl::ActorTreeAbstract* playerTree,
                    vl::ActorTreeAbstract* observatorTree);

    void render() override;
    void showOrHide() override;

private:
    void updateWindowTitle();
    void updateMenu(ViewType oocclusionViewType, bool isSecondViewActivated);

    void clearMenu();
    void setHelpText();

    vl::String getCurrentMenuContent(ViewType oocclusionViewType,
                                     const bool isSecondViewActivated) const;
    vl::Text* getActiveMenu(ViewType oocclusionViewType);

    vl::ref<vl::Text> createMenu(vl::ActorTreeAbstract*,
                                 unsigned int mask = 0xFFFFFFFF);

    bool isOptionMenuOpen{false};

    vl::ref<vl::OpenGLContext> openglContext;
    std::shared_ptr<OcclusionStatistics> statistics;
    std::shared_ptr<DoubleCamera> doubleCamera;
    std::shared_ptr<PlayerVisualizationState> playerVisualizationState;
    std::shared_ptr<ObservatorVisualizationState> observatorVisualizationState;
    std::shared_ptr<bool> previewEnabled;
    std::shared_ptr<ViewType> occlusionViewType;
    vl::ref<vl::Text> playerText;
    vl::ref<vl::Text> observatorText;

    FpsCounter fps{};
};
}
