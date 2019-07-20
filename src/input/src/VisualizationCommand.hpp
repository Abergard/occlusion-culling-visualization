#pragma once

#include <memory>

namespace ocv
{
class VisualizationView;
class VisualizationCommand
{
public:
    VisualizationCommand(std::shared_ptr<VisualizationView> ocvView)
        : view{std::move(ocvView)}
    {
    }

    virtual ~VisualizationCommand() = default;
    virtual void execute() = 0;

protected:
    std::shared_ptr<VisualizationView> view;
};
}
