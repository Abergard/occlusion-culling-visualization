#include "VlController.hpp"

#include <memory>

#include "WholeApplicationVlController.hpp"
#include "view/VisualizationView.hpp"
#include "utils/vl/MakeRef.hpp"

namespace ocv
{
vl::ref<DefaultUiEventListener>
    createWholeAppController(VisualizationView& view)
{
    return ocv::make_ref<WholeApplicationVlController>(view);
}
}
