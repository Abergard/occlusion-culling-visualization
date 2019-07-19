#include "VisualizationCommand.hpp"

namespace ocv
{
class ToggleView : public VisualizationCommand
{
public:
    using VisualizationCommand::VisualizationCommand;

    void execute() override;
};
}
