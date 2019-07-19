#include "VlController.hpp"

#include <memory>

#include "WholeApplicationVlController.hpp"
#include "view/VisualizationView.hpp"

namespace ocv
{
std::unique_ptr<DefaultUiEventListener>
    createWholeAppController(std::shared_ptr<VisualizationView> view)
{
    return std::make_unique<WholeApplicationVlController>(std::move(view));
}
}
