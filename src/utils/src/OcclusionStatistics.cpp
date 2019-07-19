#include "OcclusionStatistics.hpp"

namespace ocv
{
void OcclusionStatistics::update(int statsTotalObjects,
                                 int statsOccludedObjects)
{
    totalObjects = statsTotalObjects;
    occludedRatio = 100.0f * statsOccludedObjects / statsTotalObjects;
    nonOccludedObjects = statsTotalObjects - statsOccludedObjects;
}

float OcclusionStatistics::ratio() const
{
    return occludedRatio;
}

int OcclusionStatistics::nonOccluded() const
{
    return nonOccludedObjects;
}

int OcclusionStatistics::total() const
{
    return totalObjects;
}
}
