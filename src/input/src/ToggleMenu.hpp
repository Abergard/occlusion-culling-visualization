#include "VisualizationCommand.hpp"

namespace ocv
{
class ToggleMenu : public VisualizationCommand
{
public:
    using VisualizationCommand::VisualizationCommand;

    void execute() override;
};
}
