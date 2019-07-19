#include "VisualizationCommand.hpp"

namespace ocv
{
class TogglePlayerAABBDraw : public VisualizationCommand
{
public:
    using VisualizationCommand::VisualizationCommand;

    void execute() override;
};
}
