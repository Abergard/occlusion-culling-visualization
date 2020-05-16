#pragma once

#include <memory>

namespace vl
{
class OpenGLContext;
class ActorTreeAbstract;
}

namespace ocv
{
class OcclusionStatistics;
class DoubleCamera;
struct ObservatorVisualizationState;
struct PlayerVisualizationState;
enum class ViewType;

class menu
{
public:
    virtual ~menu() = default;

    virtual void render() = 0;
    virtual void showOrHide() = 0;
};

std::unique_ptr<menu>
    createInformationMenu(vl::OpenGLContext* context,
                          std::shared_ptr<OcclusionStatistics>,
                          DoubleCamera&,
                          std::shared_ptr<PlayerVisualizationState>,
                          std::shared_ptr<ObservatorVisualizationState>,
                          std::shared_ptr<bool> preview,
                          std::shared_ptr<ViewType> viewType,
                          vl::ActorTreeAbstract* playerTree,
                          vl::ActorTreeAbstract* observatorTree);
}
