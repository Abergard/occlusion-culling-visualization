#include "ToggleVisualizationEffect.hpp"

#include "view/VisualizationView.hpp"

namespace ocv
{
void ToggleVisualizationEffect::execute()
{
    view->enableDisableRenderingWhatPlayerRender();
}
}
