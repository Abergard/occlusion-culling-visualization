#include "VisualizationCommand.hpp"

namespace ocv
{
class ToggleEditorMode : public VisualizationCommand
{
public:
    using VisualizationCommand::VisualizationCommand;

    void execute() override;
};
}
