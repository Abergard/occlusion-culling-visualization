#include "VisualizationCommand.hpp"

namespace ocv
{
class ToggleObserverAABBDraw : public VisualizationCommand
{
public:
    using VisualizationCommand::VisualizationCommand;

    void execute() override;
};
}
