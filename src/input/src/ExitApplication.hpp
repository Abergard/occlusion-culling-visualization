#include "VisualizationCommand.hpp"

namespace ocv
{
class ExitApplication : public VisualizationCommand
{
public:
    using VisualizationCommand::VisualizationCommand;

    void execute() override;
};
}
