#include "ExitApplication.hpp"

#include "view/VisualizationView.hpp"

namespace ocv
{
void ExitApplication::execute()
{
    view.closeApplication();
}
}
