#include "VisualizationCommand.hpp"

namespace ocv
{
class ToggleActiveView : public VisualizationCommand
{
public:
    using VisualizationCommand::VisualizationCommand;

    void execute() override;
};
}
