#include "VisualizationCommand.hpp"

namespace ocv
{
class ToggleVisualizationEffect : public VisualizationCommand
{
public:
    using VisualizationCommand::VisualizationCommand;

    void execute() override;
};
}
