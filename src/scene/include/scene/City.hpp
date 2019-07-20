#pragma once

#include <vlGraphics/ActorTreeAbstract.hpp>
#include <vlGraphics/Effect.hpp>
#include <vlGraphics/SceneManagerActorKdTree.hpp>

#include "camera/DoubleCamera.hpp"
#include "scene/GlobalIllumination.hpp"
#include "utils/vl/MakeRef.hpp"

namespace ocv
{
class City
{
public:
    City(std::shared_ptr<DoubleCamera>);

    vl::SceneManagerActorKdTree* sceneManager();

private:
    void prepareCity(vl::ref<vl::ActorTreeAbstract> tree);
    void generateTrees(vl::ref<vl::ActorTreeAbstract> tree, float groundSize);

    GlobalIllumination globalLights;
    std::shared_ptr<DoubleCamera> cameras;

    vl::ref<vl::SceneManagerActorKdTree> mSceneManagerActorTree =
        make_ref<vl::SceneManagerActorKdTree>();
};
}
