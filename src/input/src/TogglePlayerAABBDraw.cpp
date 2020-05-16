#include "TogglePlayerAABBDraw.hpp"

#include "view/VisualizationView.hpp"

namespace ocv
{
void TogglePlayerAABBDraw::execute()
{
    view.togglePlayerAABBDraw();
}
}
