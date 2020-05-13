#pragma once

#include "VlController.hpp"

#include <map>
#include <memory>
#include <vlCore/vlnamespace.hpp>

#include "VisualizationCommand.hpp"
#include "utils/DefaultUiEventListener.hpp"

namespace ocv
{
class VisualizationView;
class WholeApplicationVlController : public DefaultUiEventListener
{
public:
    WholeApplicationVlController(std::shared_ptr<VisualizationView>);

    void keyPressEvent(unsigned short /*ch*/, vl::EKey key) override;

private:
    std::map<vl::EKey, std::unique_ptr<VisualizationCommand>> commands;
    std::shared_ptr<VisualizationView> occlusionVisualizationView;
};
}
