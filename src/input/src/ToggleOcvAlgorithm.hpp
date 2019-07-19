#include "VisualizationCommand.hpp"

namespace ocv
{
class ToggleOcvAlgorithm : public VisualizationCommand
{
public:
    using VisualizationCommand::VisualizationCommand;

    void execute() override;
};
}
