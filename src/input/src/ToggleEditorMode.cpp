#include "ToggleEditorMode.hpp"

#include "view/VisualizationView.hpp"

namespace ocv
{
void ToggleEditorMode::execute()
{
    view.enterExitEditorMode();
}
}
