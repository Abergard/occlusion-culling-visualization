#include "BuildingLoader.hpp"

#include "XmlBuildingLoader.hpp"
#include "utils/FileAccess.hpp"

namespace ocv
{
std::unique_ptr<BuildingLoader> createXmlBuildingLoader(CityPlanFilePath path)
{
    return std::make_unique<XmlBuildingLoader>(createStandardFileAccess(),
                                               std::move(path));
}
}
