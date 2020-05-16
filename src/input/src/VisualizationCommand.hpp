#pragma once

#include <memory>

namespace ocv
{
class VisualizationView;
class VisualizationCommand
{
public:
    VisualizationCommand(VisualizationView& ocvView)
        : view{ocvView}
    {
    }

    virtual ~VisualizationCommand() = default;
    virtual void execute() = 0;

protected:
    VisualizationView& view;
};
}
