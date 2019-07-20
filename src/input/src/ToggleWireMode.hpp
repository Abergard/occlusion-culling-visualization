#include "VisualizationCommand.hpp"

namespace ocv
{
class ToggleWireMode : public VisualizationCommand
{
public:
    using VisualizationCommand::VisualizationCommand;

    void execute() override;
};
}
