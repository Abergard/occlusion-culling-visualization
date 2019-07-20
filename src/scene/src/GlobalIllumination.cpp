#include "GlobalIllumination.hpp"

#include "utils/vl/MakeRef.hpp"

namespace ocv
{
namespace
{
auto sunLight = make_ref<vl::Light>();
}

GlobalIllumination::GlobalIllumination() : sun{sunLight.get()}
{
    float ambient = 0.3f;
    float diffuse = 0.7f;

    float globalAmbient[] = {ambient, ambient, ambient, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    sun->setDiffuse(vl::fvec4(diffuse, diffuse, diffuse, 1.0f));
    sun->setAmbient(vl::fvec4(ambient, ambient, ambient, 1.0f));
}
}
