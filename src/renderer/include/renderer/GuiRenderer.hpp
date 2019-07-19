#pragma once

#include <vlGraphics/RenderQueue.hpp>
#include <vlGraphics/Renderer.hpp>

namespace ocv
{
class GuiRenderer : public vl::Renderer
{
public:
    GuiRenderer();

    const vl::RenderQueue* render(const vl::RenderQueue*,
                                  vl::Camera*,
                                  vl::real frameClock) override;
};
}
