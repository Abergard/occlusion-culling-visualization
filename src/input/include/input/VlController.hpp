#pragma once

#include <memory>
#include <vlCore/vlnamespace.hpp>
#include <vlCore/Object.hpp>

namespace ocv
{
class DefaultUiEventListener;
class VisualizationView;

vl::ref<DefaultUiEventListener> createWholeAppController(VisualizationView&);
}
