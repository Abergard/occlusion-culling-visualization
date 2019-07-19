#pragma once

#include <vlGraphics/Light.hpp>

namespace ocv
{
class GlobalIllumination
{
public:
    GlobalIllumination();

    vl::Light* sun;
};
}
