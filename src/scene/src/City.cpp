#include "City.hpp"

#include <memory>
#include <vlCore/Vector3.hpp>
#include <vlGraphics/GeometryPrimitives.hpp>

#include "utils/BuildingLoader.hpp"
#include "utils/vl/Log.hpp"
#include "utils/vl/MakeRef.hpp"

namespace ocv
{
namespace
{
auto createEffectBuilding(GlobalIllumination& globalLights)
{
    auto buildingEffect = make_ref<vl::Effect>();
    auto shader = buildingEffect->shader();

    shader->enable(vl::EN_DEPTH_TEST);
    shader->enable(vl::EN_CULL_FACE);
    shader->enable(vl::EN_LINE_SMOOTH);
    shader->enable(vl::EN_LIGHTING);
    shader->setRenderState(globalLights.sun, 0);

    constexpr float ambient = 0.8f;
    shader->gocMaterial()->setAmbient(
        vl::fvec4(ambient, ambient, ambient, 1.0f));

    return buildingEffect;
}

auto createGround(float groundSize)
{
    auto ground =
        vl::makeGrid(vl::vec3(0, -1.0f, 0), groundSize, groundSize, 100, 100);

    ground->computeNormals();
    return ground;
}
}

City::City(std::shared_ptr<DoubleCamera> doubleCamera)
    : cameras{std::move(doubleCamera)}
{
    prepareCity(mSceneManagerActorTree->tree());
}

void City::prepareCity(vl::ref<vl::ActorTreeAbstract> tree)
{
    Debug("prepare city");
    auto buildingEffect = createEffectBuilding(globalLights);
    auto sunTransform =
        make_ref<vl::Transform>(vl::mat4::getTranslation(200, 300, 60));
    globalLights.sun->bindTransform(sunTransform.get());

    // Create ground
    constexpr float groundSize = 10000;
    auto ground = createGround(groundSize);
    ground->computeNormals();
    auto groundEffect = make_ref<vl::Effect>();
    auto groundShader = groundEffect->shader();
    groundShader->gocColor()->setValue(vl::green);
    groundShader->enable(vl::EN_DEPTH_TEST);
    groundShader->enable(vl::EN_CULL_FACE);
    groundShader->enable(vl::EN_LIGHTING);
    groundShader->gocMaterial()->setAmbient(vl::black);
    groundShader->setRenderState(globalLights.sun, 0);
    groundShader->gocMaterial();
    auto groundActor = tree->addActor(ground.get(), groundEffect.get(), NULL);
    groundActor->setOccludee(false);
    groundActor->setEnableMask(0x10000000);

    // Create sun object
    vl::ref<vl::Geometry> sunGeometry =
        vl::makeUVSphere(vl::vec3(0, 0, 0), 45.0f);
    vl::ref<vl::Effect> sunEffect = new vl::Effect;
    sunEffect->shader()->enable(vl::EN_DEPTH_TEST);
    sunEffect->shader()->gocColor()->setValue(
        vl::vec4{0.992f, 0.722f, 0.075f, 1});
    sunEffect->shader()->enable(vl::EN_CULL_FACE);
    auto sunActor =
        tree->addActor(sunGeometry.get(), sunEffect.get(), sunTransform.get());
    sunActor->setOccludee(true);
    sunActor->setEnableMask(0x10000000);

    // Create player object
    auto playerGeomtry = vl::makePyramid(vl::vec3(0, 0, 0), 15, 15);
    auto playerEffect = make_ref<vl::Effect>();
    playerEffect->shader()->enable(vl::EN_DEPTH_TEST);
    playerEffect->shader()->enable(vl::EN_LINE_SMOOTH);
    playerEffect->shader()->enable(vl::EN_POLYGON_OFFSET_LINE);
    playerEffect->shader()->gocColor()->setValue(vl::white);
    playerEffect->shader()->enable(vl::EN_CULL_FACE);
    playerEffect->lod(0)->push_back(new vl::Shader);
    auto shader = playerEffect->shader(0, 1);
    shader->enable(vl::EN_DEPTH_TEST);
    shader->enable(vl::EN_LINE_SMOOTH);
    shader->enable(vl::EN_POLYGON_OFFSET_LINE);
    shader->enable(vl::EN_CULL_FACE);
    shader->gocPolygonMode()->set(vl::PM_LINE, vl::PM_LINE);
    shader->gocColor()->setValue(vl::gray);
    auto playerTransform =
        make_ref<vl::Transform>(vl::mat4::getTranslation(0, 0, 0) *
                                vl::mat4::getRotationZYX(0, 0, -90));
    auto playerActor = tree->addActor(
        playerGeomtry.get(), playerEffect.get(), playerTransform.get());
    playerActor->setOccludee(false);
    playerActor->setEnableMask(0x10000000);

    auto player =
        make_ref<vl::Transform>(vl::mat4::getTranslation(200, 10, 60));
    player->addChild(playerTransform.get());
    cameras->playerCamera()->bindTransform(player.get());

    // Load city
    auto loader = createXmlBuildingLoader("../data/city.tmx");
    const auto city = loader->load();

    // Draw city
    for (const auto& building : city)
    {
        // Make building
        auto buildingGeometry = vl::makeBox(
            vl::vec3(0, 0, 0),
            vl::vec3(building.width, building.height, building.length));
        buildingGeometry->computeNormals();
        auto buldingRotation = -1 * building.rotation;
        auto buildingTransform = make_ref<vl::Transform>(
            vl::mat4::getTranslation(building.x, 0, building.y) *
            vl::mat4::getRotationZYX(0, buldingRotation, 0));
        auto buildingActor = tree->addActor(buildingGeometry.get(),
                                            buildingEffect.get(),
                                            buildingTransform.get());
        buildingActor->setOccludee(true);
        buildingActor->setEnableMask(0x10000000);
    }
}

vl::SceneManagerActorKdTree* City::sceneManager()
{
    return mSceneManagerActorTree.get();
}
}
