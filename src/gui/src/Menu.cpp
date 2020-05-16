#include "Menu.hpp"

#include <vlGraphics/ActorTreeAbstract.hpp>
#include <vlGraphics/OpenGLContext.hpp>

#include "InformationMenu.hpp"

namespace ocv
{
std::unique_ptr<menu> createInformationMenu(
    vl::OpenGLContext* context,
    std::shared_ptr<OcclusionStatistics> statistics,
    DoubleCamera& camera,
    std::shared_ptr<PlayerVisualizationState> playerState,
    std::shared_ptr<ObservatorVisualizationState> obsevatorState,
    std::shared_ptr<bool> preview,
    std::shared_ptr<ViewType> viewType,
    vl::ActorTreeAbstract* playerTree,
    vl::ActorTreeAbstract* observatorTree)
{
    return std::make_unique<InformationMenu>(context,
                                             std::move(statistics),
                                             camera,
                                             std::move(playerState),
                                             std::move(obsevatorState),
                                             std::move(preview),
                                             std::move(viewType),
                                             playerTree,
                                             observatorTree);
}
}
