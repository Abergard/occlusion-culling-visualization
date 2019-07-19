#pragma once

#include <memory>
#include <sstream>

#include "BuildingLoader.hpp"

namespace ocv
{
class FileAccess;
class XmlBuildingLoader : public BuildingLoader
{
public:
    XmlBuildingLoader(std::shared_ptr<FileAccess>, CityPlanFilePath);

    Buildings load() const override;

private:
    std::stringstream getCityPlanXml() const;

    std::shared_ptr<FileAccess> fileAccess;
    const CityPlanFilePath cityPlanLocation;
};
}
