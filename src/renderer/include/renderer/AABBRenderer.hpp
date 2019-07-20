#pragma once

#include <vlGraphics/Renderer.hpp>

#include "utils/vl/MakeRef.hpp"

namespace ocv
{
class AABBRenderer
{
public:
    AABBRenderer(vl::ref<vl::Renderer>, bool withOcclussionTest);

    void render(const vl::RenderQueue*, vl::Camera*);

private:
    void prepareToRender(vl::Camera*);
    void cleanupAfterRender(vl::Camera*);
    void renderAABB(const vl::RenderQueue*, vl::Camera*);
    void enableScissorTest();
    void disableScissorTest();
    void doScissor(vl::Camera*);
    void prepareColorForDrawing();
    void enableVertexArrayDraw();
    void disableVertexArrayDraw();
    void setGlobalShader(vl::Camera*);
    void updateAllShaderVariable(vl::Camera*);
    void updateShaderVariableWhenTransformChanged(vl::Camera*);
    void resetGlobalShader(vl::Camera*);

    vl::Shader shader;
    vl::GLSLProgram* glslProgram{shader.glslProgram()};
    const vl::Scissor* curScissor{nullptr};
    vl::Transform* curTransform{nullptr};
    const vl::ref<vl::EnableSet> mDummyEnables{ocv::make_ref<vl::EnableSet>()};
    const vl::ref<vl::RenderStateSet> mDummyStateSet{
        ocv::make_ref<vl::RenderStateSet>()};
    vl::ref<vl::Renderer> wrappedRenderer;

    const bool withOcvTest;
};
}
