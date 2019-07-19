#pragma once

namespace ocv
{
class OcclusionStatistics
{
public:
    void update(int statsTotalObjects, int statsOccludedObjects);

    float ratio() const;
    int nonOccluded() const;
    int total() const;

private:
    float occludedRatio{0};
    int nonOccludedObjects{0};
    int totalObjects{0};
};
}
