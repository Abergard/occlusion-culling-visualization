#include "ToggleSecondView.hpp"

#include "view/VisualizationView.hpp"

namespace ocv
{
void ToggleSecondView::execute()
{
    view.hideOrShowSecondView();
}
}
