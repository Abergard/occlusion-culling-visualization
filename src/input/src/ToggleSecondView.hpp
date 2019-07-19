#include "VisualizationCommand.hpp"

namespace ocv
{
class ToggleSecondView : public VisualizationCommand
{
public:
    using VisualizationCommand::VisualizationCommand;

    void execute() override;
};
}
