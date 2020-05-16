#include "ToggleActiveView.hpp"

#include "view/VisualizationView.hpp"

namespace ocv
{
void ToggleActiveView::execute()
{
    view.toggleActiveView();
}
}
