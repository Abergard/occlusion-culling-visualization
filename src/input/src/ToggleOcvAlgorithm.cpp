#include "ToggleOcvAlgorithm.hpp"

#include "view/VisualizationView.hpp"

namespace ocv
{
void ToggleOcvAlgorithm::execute()
{
    view->enableDisableOcclusionCulling();
}
}
