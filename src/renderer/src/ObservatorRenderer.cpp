#include "ObservatorRenderer.hpp"

#include <algorithm>

#include <vlCore/Colors.hpp>
#include <vlGraphics/OpenGLContext.hpp>
#include <vlGraphics/RenderQueue.hpp>

#include "utils/vl/Log.hpp"

namespace ocv
{
ObservatorRenderer::ObservatorRenderer(
    NotOccludedActors notOccludedActorsInit,
    std::shared_ptr<ObservatorVisualizationState> state)
    : notOccludedActors{std::move(notOccludedActorsInit)},
      visualizationState{std::move(state)},
      aabbRenderer{this, false}
{
    setEnableMask(defaultMask | wireModeMask);
    VL_CHECK_OGL();
}

const vl::RenderQueue* ObservatorRenderer::render(const vl::RenderQueue* queue,
                                                  vl::Camera* camera,
                                                  vl::real frameClock)
{
    if (visualizationState->observatorState && visualizationState->wireState)
    {
        renderAllButWhatPlayerCanNotSeeInWireMode(queue, camera, frameClock);
    }
    else if (visualizationState->observatorState)
    {
        renderOnlyWhatPlayerCanSee(camera, frameClock);
    }
    else
    {
        renderAllInNormalMode(queue, camera, frameClock);
    }

    return queue;
}

const vl::RenderQueue*
    ObservatorRenderer::renderOnlyWhatPlayerCanSee(vl::Camera* camera,
                                                   vl::real frameClock)
{
    return renderAllInNormalMode(notOccludedActors.get(), camera, frameClock);
}

const vl::RenderQueue*
    ObservatorRenderer::renderAllInNormalMode(const vl::RenderQueue* queue,
                                              vl::Camera* camera,
                                              vl::real frameClock)
{
    setNormalModeMask(queue);
    vl::Renderer::render(queue, camera, frameClock);

    VL_CHECK_OGL();

    if (visualizationState->aabbState)
    {
        aabbRenderer.render(queue, camera);
    }
    return queue;
}

void ObservatorRenderer::setNormalModeMask(const vl::RenderQueue* queue)
{
    for (int i = 0; i < queue->size(); ++i)
    {
        if (isEnabled(queue->at(i)->mActor))
        {
            queue->at(i)->mActor->setEnableMask(defaultMask);
        }
    }
}

const vl::RenderQueue*
    ObservatorRenderer::renderAllButWhatPlayerCanNotSeeInWireMode(
        const vl::RenderQueue* queue,
        vl::Camera* camera,
        vl::real frameClock)
{
    setWireModeMaskForOccludee(queue);
    setNormalModeMask(notOccludedActors.get());
    vl::Renderer::render(queue, camera, frameClock);

    VL_CHECK_OGL();

    if (visualizationState->aabbState)
    {
        aabbRenderer.render(queue, camera);
    }
    return queue;
}

void ObservatorRenderer::setWireModeMaskForOccludee(
    const vl::RenderQueue* queue)
{
    for (int i = 0; i < queue->size(); ++i)
    {
        auto actor = queue->at(i)->mActor;
        if (actor->isOccludee())
        {
            actor->setEnableMask(wireModeMask);
        }
    }
}
}
