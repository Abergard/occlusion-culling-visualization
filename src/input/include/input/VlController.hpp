#pragma once

#include <memory>
#include <vlCore/vlnamespace.hpp>

namespace ocv
{
class DefaultUiEventListener;
class VisualizationView;

std::unique_ptr<DefaultUiEventListener>
    createWholeAppController(std::shared_ptr<VisualizationView>);
}
