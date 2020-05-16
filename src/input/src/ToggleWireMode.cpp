#include "ToggleWireMode.hpp"

#include "view/VisualizationView.hpp"

namespace ocv
{
void ToggleWireMode::execute()
{
    view.enableDisableWireModeForOcluded();
}
}
