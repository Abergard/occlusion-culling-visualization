#pragma once

#include <memory>
#include <string>
#include <vector>

namespace ocv
{
struct Building
{
    float x;
    float y;
    float width;
    float length;
    float height;
    float rotation;
};

using Buildings = std::vector<Building>;
class BuildingLoader
{
public:
    virtual Buildings load() const = 0;
};

using CityPlanFilePath = std::string;

std::unique_ptr<BuildingLoader> createXmlBuildingLoader(CityPlanFilePath);
}
