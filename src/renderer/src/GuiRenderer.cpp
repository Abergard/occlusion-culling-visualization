#include "GuiRenderer.hpp"

#include "utils/vl/Log.hpp"
#include "utils/vl/MakeRef.hpp"

namespace ocv
{
GuiRenderer::GuiRenderer()
{
    vl::Renderer::setClearFlags(vl::CF_DO_NOT_CLEAR);
    vl::Renderer::setEnableMask(0x01000000);
}

const vl::RenderQueue* GuiRenderer::render(const vl::RenderQueue* queue,
                                           vl::Camera* camera,
                                           vl::real frameClock)
{
    vl::RenderQueue q;

    for (int i = 0; i < queue->size(); ++i)
    {
        if (vl::Renderer::isEnabled(queue->at(i)->mActor))
        {
            *(q.newToken(false)) = *queue->at(i);
        }
    }

    vl::Renderer::render(&q, camera, frameClock);

    return queue;
}
}
