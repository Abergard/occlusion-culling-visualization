#pragma once

#include <vlGraphics/RenderQueue.hpp>
#include <vlGraphics/Renderer.hpp>

#include "AABBRenderer.hpp"
#include "NotOccludedActors.hpp"
#include "utils/VisualizationState.hpp"
#include "utils/vl/MakeRef.hpp"

namespace ocv
{
class ObservatorRenderer : public vl::Renderer
{
public:
    ObservatorRenderer(NotOccludedActors,
                       std::shared_ptr<ObservatorVisualizationState>);

    const vl::RenderQueue* render(const vl::RenderQueue*,
                                  vl::Camera*,
                                  vl::real frameClock) override;

private:
    void setNormalModeMask(const vl::RenderQueue*);
    void setWireModeMaskForOccludee(const vl::RenderQueue*);
    const vl::RenderQueue* renderOnlyWhatPlayerCanSee(vl::Camera*,
                                                      vl::real frameClock);

    const vl::RenderQueue*
        renderAllButWhatPlayerCanNotSeeInWireMode(const vl::RenderQueue*,
                                                  vl::Camera*,
                                                  vl::real frameClock);

    const vl::RenderQueue* renderAllInNormalMode(const vl::RenderQueue*,
                                                 vl::Camera*,
                                                 vl::real frameClock);

    const unsigned int defaultMask{0x10000000};
    const unsigned int wireModeMask{0x00000001};

    NotOccludedActors notOccludedActors;
    std::shared_ptr<ObservatorVisualizationState> visualizationState;
    vl::ref<vl::Shader> shader = ocv::make_ref<vl::Shader>();
    vl::ref<vl::RenderQueue> queue{ocv::make_ref<vl::RenderQueue>()};
    AABBRenderer aabbRenderer;
};
}
