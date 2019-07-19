#include "AABBRenderer.hpp"

#include <vlGraphics/OpenGLContext.hpp>
#include <vlGraphics/RenderQueue.hpp>

#include "utils/vl/Log.hpp"

// TODO: refactor this class
namespace ocv
{
AABBRenderer::AABBRenderer(vl::ref<vl::Renderer> renderer,
                           bool withOcclussionTest)
    : wrappedRenderer{renderer}, withOcvTest{withOcclussionTest}
{
    VL_CHECK(wrappedRenderer);

    shader.gocDepthMask()->set(false);
    shader.gocDepthFunc()->set(vl::FU_LEQUAL);
    shader.gocColorMask()->set(false, false, false, false);
    shader.enable(vl::EN_CULL_FACE);
    shader.enable(vl::EN_DEPTH_TEST);
    shader.enable(vl::EN_POLYGON_OFFSET_FILL);
    shader.gocPolygonOffset()->set(-1.0f, -1.0f);

    if (!withOcvTest)
    {
        shader.gocColorMask()->set(true, true, true, true);
        shader.gocPolygonMode()->set(vl::PM_LINE, vl::PM_LINE);
    }
}

void AABBRenderer::render(const vl::RenderQueue* inRenderQueue,
                          vl::Camera* camera)
{
    prepareToRender(camera);
    renderAABB(inRenderQueue, camera);
    cleanupAfterRender(camera);
}

void AABBRenderer::prepareToRender(vl::Camera* camera)
{
    enableScissorTest();
    doScissor(camera);
    setGlobalShader(camera);
    updateAllShaderVariable(camera);
    if (!withOcvTest)
    {
        prepareColorForDrawing();
    }
    enableVertexArrayDraw();
}

void AABBRenderer::cleanupAfterRender(vl::Camera* camera)
{
    disableVertexArrayDraw();
    resetGlobalShader(camera);
    disableScissorTest();
}

void AABBRenderer::renderAABB(const vl::RenderQueue* inRenderQueue,
                              vl::Camera* camera)
{
    for (int i = 0; i < inRenderQueue->size(); ++i)
    {
        const auto* tok = inRenderQueue->at(i);
        auto* actor = tok->mActor;

        if (!wrappedRenderer->isEnabled(actor->enableMask()))
            continue;

        const auto* scissor =
            actor->scissor() ? actor->scissor() : tok->mShader->scissor();

        if (curScissor != scissor)
        {
            curScissor = scissor;
            if (curScissor)
            {
                curScissor->enable(camera->viewport());
            }
            else
            {
                // scissor the viewport by default: needed for points and lines
                // with size > 1.0 as they are not clipped against the
                // viewport.
                VL_CHECK(glIsEnabled(GL_SCISSOR_TEST))
                glScissor(camera->viewport()->x(),
                          camera->viewport()->y(),
                          camera->viewport()->width(),
                          camera->viewport()->height());
            }
        }
        auto box = actor->boundingBox();

        if (actor->isOccludee())
        {
            if (tok->mActor->transform() != curTransform)
            {
                curTransform = tok->mActor->transform();
                updateShaderVariableWhenTransformChanged(camera);
            }

            if (withOcvTest)
                actor->setOcclusionQueryTick(wrappedRenderer->renderTick());

            const vl::AABB& aabb = tok->mRenderable->boundingBox();
            const float verts[] = {
                (float)aabb.minCorner().x(), (float)aabb.minCorner().y(),
                (float)aabb.minCorner().z(), (float)aabb.maxCorner().x(),
                (float)aabb.minCorner().y(), (float)aabb.minCorner().z(),
                (float)aabb.maxCorner().x(), (float)aabb.maxCorner().y(),
                (float)aabb.minCorner().z(), (float)aabb.minCorner().x(),
                (float)aabb.maxCorner().y(), (float)aabb.minCorner().z(),
                (float)aabb.minCorner().x(), (float)aabb.minCorner().y(),
                (float)aabb.maxCorner().z(), (float)aabb.maxCorner().x(),
                (float)aabb.minCorner().y(), (float)aabb.maxCorner().z(),
                (float)aabb.maxCorner().x(), (float)aabb.maxCorner().y(),
                (float)aabb.maxCorner().z(), (float)aabb.minCorner().x(),
                (float)aabb.maxCorner().y(), (float)aabb.maxCorner().z()};
            const unsigned quads[] = {3, 2, 1, 0, 2, 6, 5, 1, 3, 7, 6, 2,
                                      7, 3, 0, 4, 4, 0, 1, 5, 6, 7, 4, 5};
            glVertexPointer(3, GL_FLOAT, 0, verts);
            VL_CHECK_OGL();
            if (withOcvTest)
            {
                actor->createOcclusionQuery();
                VL_CHECK_OGL();
                vl::glBeginQuery(GL_SAMPLES_PASSED, actor->occlusionQuery());
                VL_CHECK_OGL();
            }
            glDrawElements(GL_QUADS, 6 * 4, GL_UNSIGNED_INT, quads);
            VL_CHECK_OGL();
            if (withOcvTest)
            {
                vl::glEndQuery(GL_SAMPLES_PASSED);
                VL_CHECK_OGL();
            }
        }
    }
}

void AABBRenderer::enableScissorTest()
{
    glEnable(GL_SCISSOR_TEST);
}

void AABBRenderer::disableScissorTest()
{
    glDisable(GL_SCISSOR_TEST);
}

void AABBRenderer::doScissor(vl::Camera* camera)
{
    glScissor(camera->viewport()->x(),
              camera->viewport()->y(),
              camera->viewport()->width(),
              camera->viewport()->height());
}

void AABBRenderer::prepareColorForDrawing()
{
    glColor3f(1.0f, 0.0f, 1.0f); // for debugging only
}

void AABBRenderer::enableVertexArrayDraw()
{
    glEnableClientState(GL_VERTEX_ARRAY);
}

void AABBRenderer::disableVertexArrayDraw()
{
    glDisableClientState(GL_VERTEX_ARRAY);
}

void AABBRenderer::setGlobalShader(vl::Camera* camera)
{
    wrappedRenderer->framebuffer()->openglContext()->resetRenderStates();
    wrappedRenderer->framebuffer()->openglContext()->applyRenderStates(
        shader.getRenderStateSet(), camera);
    wrappedRenderer->framebuffer()->openglContext()->resetEnables();
    wrappedRenderer->framebuffer()->openglContext()->applyEnables(
        shader.getEnableSet());
}

void AABBRenderer::updateAllShaderVariable(vl::Camera* camera)
{
    wrappedRenderer->projViewTransfCallback()->updateMatrices(
        true, true, glslProgram, camera, curTransform);
}

void AABBRenderer::updateShaderVariableWhenTransformChanged(vl::Camera* camera)
{
    wrappedRenderer->projViewTransfCallback()->updateMatrices(
        false, true, glslProgram, camera, curTransform);
}

void AABBRenderer::resetGlobalShader(vl::Camera* camera)
{
    wrappedRenderer->framebuffer()->openglContext()->applyEnables(
        mDummyEnables.get());
    wrappedRenderer->framebuffer()->openglContext()->applyRenderStates(
        mDummyStateSet.get(), camera);
}
}
