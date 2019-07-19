#include "XmlBuildingLoader.hpp"

#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <boost/range/algorithm/copy.hpp>

#include "utils/FileAccess.hpp"

using boost::property_tree::ptree;

namespace ocv
{
namespace
{
ptree getCityPlan(std::stringstream cityPlanXml)
{
    ptree cityPlan;
    read_xml(std::move(cityPlanXml), cityPlan);
    return cityPlan;
}

ptree& removeAttributesFromNodeIfExist(ptree& node)
{
    if (!node.empty() && node.front().first == "<xmlattr>")
    {
        node.pop_front();
    }
    return node;
}
ptree& getBuildings(ptree& cityPlan)
{
    auto& b = cityPlan.get_child("map.objectgroup");
    removeAttributesFromNodeIfExist(b);
    return b;
}

Building readBuilding(const ptree& buildingAtt)
{
    return {buildingAtt.get<float>("x"),
            buildingAtt.get<float>("y"),
            buildingAtt.get<float>("width"),
            buildingAtt.get<float>("height"),
            buildingAtt.get<float>("type") * 1.5f,
            buildingAtt.get<float>("rotation", 0.0f)};
}
}

XmlBuildingLoader::XmlBuildingLoader(std::shared_ptr<FileAccess> fa,
                                     CityPlanFilePath planFilePath)
    : fileAccess{std::move(fa)}, cityPlanLocation(std::move(planFilePath))
{
}

std::stringstream XmlBuildingLoader::getCityPlanXml() const
{
    return std::stringstream{fileAccess->read(cityPlanLocation)};
}

Buildings XmlBuildingLoader::load() const
{
    auto cityPlan = getCityPlan(getCityPlanXml());

    Buildings b;
    b.reserve(cityPlan.size());

    for (const auto& building : getBuildings(cityPlan))
    {
        b.push_back(readBuilding(building.second.get_child("<xmlattr>")));
    }

    return b;
}
}
