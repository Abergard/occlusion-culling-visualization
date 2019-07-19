#pragma once

namespace ocv
{
enum class VisualizationMajorState
{
    Normal = 0,
    Wire,
    Disabled
};

struct PlayerVisualizationState
{
    bool aabbState;
    bool occlusionCullingState;
};

struct ObservatorVisualizationState
{
    bool aabbState;
    bool wireState;
    bool observatorState;
};
}
