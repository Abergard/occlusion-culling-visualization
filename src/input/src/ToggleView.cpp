#include "ToggleView.hpp"

#include "view/VisualizationView.hpp"

namespace ocv
{
void ToggleView::execute()
{
    view->switchBetweenMainAndSecondView();
}
}
