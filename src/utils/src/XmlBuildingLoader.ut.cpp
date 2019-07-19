#include <gtest/gtest.h>
#include <string>

#include "utils/MockFileAccess.hpp"

#include "XmlBuildingLoader.hpp"

using namespace ::testing;

namespace ocv
{
namespace
{
const auto city1 = R"(<?xml version="1.0" encoding="UTF-8"?>
<map version="1.0" tiledversion="1.1.4" orientation="orthogonal" renderorder="right-down" width="50" height="50" tilewidth="8" tileheight="8" infinite="0" nextobjectid="11">
 <objectgroup name="city">
  <object id="1" type="1" x="24.0682" y="48.4318" width="16" height="16"/>
  <object id="5" type="0" x="56.25" y="48" width="16" height="16" rotation="45"/>
  <object id="6" type="2" x="25.25" y="23.75" width="48.5" height="16"/>
  <object id="7" type="0" x="56" y="72" width="8.25" height="8.25"/>
  <object id="8" type="1" x="31.375" y="71.875" width="8.25" height="8.25"/>
  <object id="9" type="2" x="93.75" y="24" width="16.5" height="79.5"/>
  <object id="10" type="2" x="2.25" y="0.25" width="16.5" height="79.5"/>
 </objectgroup>
</map>)";
}
class XmlBuildingLoaderTest : public ::Test
{
public:
    void verifyBuilding(const float height,
                         const float x,
                         const float y,
                         const float width,
                         const float length,
                         const float rotation,
                         const Building& b)
    {
        EXPECT_EQ(width, b.width);
        EXPECT_NEAR(x, b.x, 0.01);
        EXPECT_NEAR(y, b.y, 0.01);
        EXPECT_NEAR(length, b.length, 0.01);
        EXPECT_NEAR(height * 1.5f, b.height, 0.01);
        EXPECT_NEAR(rotation, b.rotation, 0.01);
    }

    std::shared_ptr<MockFileAccess> fileAccess =
        std::make_shared<StrictMock<MockFileAccess>>();
};

TEST_F(XmlBuildingLoaderTest, test)
{
    const auto cityFilePath = "some/path/to/city1";
    EXPECT_CALL(*fileAccess, read(cityFilePath)).WillOnce(Return(city1));

    XmlBuildingLoader city{fileAccess, cityFilePath};
    const auto buildings = city.load();

    const auto numberOfBuildings = 7U;
    ASSERT_EQ(numberOfBuildings, buildings.size());

    verifyBuilding(1.0f, 24.0682f, 48.4318f, 16.f, 16.f, 0.0f, buildings[0]);
    verifyBuilding(0.0f, 56.25f, 48.f, 16.f, 16.f, 45.0f, buildings[1]);
    verifyBuilding(2.0f, 25.25f, 23.75f, 48.5f, 16.f, 0.0f, buildings[2]);
    verifyBuilding(0.0f, 56.f, 72.f, 8.25f, 8.25f, 0.0f, buildings[3]);
    verifyBuilding(1.0f, 31.375f, 71.875f, 8.25f, 8.25f, 0.0f, buildings[4]);
    verifyBuilding(2.0f, 93.75f, 24.f, 16.5f, 79.5f, 0.0f, buildings[5]);
    verifyBuilding(2.0f, 2.25f, 0.25f, 16.5f, 79.5f, 0.0f, buildings[6]);
}
}
