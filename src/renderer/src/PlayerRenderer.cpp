#include "PlayerRenderer.hpp"

#include <vlGraphics/OpenGLContext.hpp>
#include <vlGraphics/RenderQueue.hpp>

#include <sstream>

#include "utils/vl/Log.hpp"
#include "utils/vl/MakeRef.hpp"

namespace ocv
{
PlayerRenderer::PlayerRenderer(NotOccludedActors notOccludedActorsInit,
                               std::shared_ptr<PlayerVisualizationState> state,
                               std::shared_ptr<OcclusionStatistics> statistics)
    : notOccludedActors{std::move(notOccludedActorsInit)},
      aabbRenderer{this, false},
      aabbRendererOcv{this, true},
      visualizationState{std::move(state)},
      occlusionStatistics{std::move(statistics)}
{
}

const vl::RenderQueue* PlayerRenderer::render(const vl::RenderQueue* queue,
                                              vl::Camera* camera,
                                              vl::real frameClock)
{
    obtainNotOccludedActors(queue);
    vl::Renderer::render(notOccludedActors.get(), camera, frameClock);

    VL_CHECK_OGL();

    if (visualizationState->aabbState)
    {
        aabbRenderer.render(notOccludedActors.get(), camera);
    }
    if (visualizationState->occlusionCullingState)
    {
        aabbRendererOcv.render(queue, camera);
    }

    return queue;
}

void PlayerRenderer::obtainNotOccludedActors(const vl::RenderQueue* queue)
{
    int statsOccludedObjects = 0;
    notOccludedActors->clear();

    if (visualizationState->occlusionCullingState)
    {
        for (int i = 0; i < queue->size(); ++i)
        {
            auto token = queue->at(i);

            if (isOccluded(token->mActor))
            {
                statsOccludedObjects++;
            }
            else
            {
                addNewTokenIfEnabled(token);
            }
        }
    }
    else
    {
        for (int i = 0; i < queue->size(); ++i)
        {
            addNewTokenIfEnabled(queue->at(i));
        }
    }

    occlusionStatistics->update(queue->size(), statsOccludedObjects);
}

void PlayerRenderer::addNewTokenIfEnabled(const vl::RenderToken* token)
{
    if (isEnabled(token->mActor))
    {
        *(notOccludedActors->newToken(false)) = *token;
    }
}

bool PlayerRenderer::isOccluded(const vl::Actor* actor) const
{
    if (validOcclusionQueryTick(actor))
    {
        GLint pixels = 0;
        vl::glGetQueryObjectiv(
            actor->occlusionQuery(), GL_QUERY_RESULT, &pixels);

        VL_CHECK_OGL();

        if (pixels <= mOcclusionThreshold)
        {
            return true;
        }
    }
    else if (actor->isOccludee())
    {
        return true;
    }
    return false;
}

bool PlayerRenderer::validOcclusionQueryTick(const vl::Actor* actor) const
{
    return actor->occlusionQuery() &&
           actor->occlusionQueryTick() == renderTick();
}
}
