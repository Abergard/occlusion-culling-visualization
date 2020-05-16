#include "ToggleObserverAABBDraw.hpp"

#include "view/VisualizationView.hpp"

namespace ocv
{
void ToggleObserverAABBDraw::execute()
{
    view.toggleObservatorAABBDraw();
}
}
