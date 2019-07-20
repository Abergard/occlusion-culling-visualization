#pragma once

#include <vlGraphics/RenderToken.hpp>
#include <vlGraphics/Renderer.hpp>

#include "AABBRenderer.hpp"
#include "NotOccludedActors.hpp"
#include "utils/OcclusionStatistics.hpp"
#include "utils/VisualizationState.hpp"

namespace ocv
{
class PlayerRenderer : public vl::Renderer
{
public:
    PlayerRenderer(NotOccludedActors,
                   std::shared_ptr<PlayerVisualizationState>,
                   std::shared_ptr<OcclusionStatistics>);

    const vl::RenderQueue* render(const vl::RenderQueue*,
                                  vl::Camera*,
                                  vl::real frameClock) override;

private:
    void obtainNotOccludedActors(const vl::RenderQueue*);
    bool validOcclusionQueryTick(const vl::Actor*) const;
    bool isOccluded(const vl::Actor*) const;

    void addNewTokenIfEnabled(const vl::RenderToken*);

    int mOcclusionThreshold{0};

    NotOccludedActors notOccludedActors;
    AABBRenderer aabbRenderer;
    AABBRenderer aabbRendererOcv;
    std::shared_ptr<PlayerVisualizationState> visualizationState;
    std::shared_ptr<OcclusionStatistics> occlusionStatistics;
};
}
