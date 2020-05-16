#pragma once

#include <memory>
#include <string>

#include <vlCore/VisualizationLibrary.hpp>

#include "camera/DoubleCamera.hpp"
#include "input/VlController.hpp"
#include "utils/vl/Log.hpp"
#include "view/VisualizationView.hpp"
#include "window/Window.hpp"

struct ScreenSize
{
    int width;
    int height;
};

ScreenSize getFullScreenSize()
{
    return ScreenSize{GetSystemMetrics(SM_CXSCREEN),
                      GetSystemMetrics(SM_CYSCREEN)};
}

int start(const ScreenSize& mainScreen)
try
{
    vl::VisualizationLibrary::init();
    Debug("Win32 main");

    Debug("width: " + std::to_string(mainScreen.width));
    Debug("height: " + std::to_string(mainScreen.height));

    constexpr auto windowTitle{"Occlusion Culling"};

    // const auto window = std::shared_ptr<ocv::Window>(ocv::createWin32Window(
    //     windowTitle, mainScreen.width, mainScreen.height));
    const auto window = ocv::createGlfwWindow(
        windowTitle, mainScreen.width, mainScreen.height);
    const auto camera = std::make_shared<ocv::DoubleCamera>(*window);
    const auto view = std::shared_ptr<ocv::VisualizationView>(
        createVisualizationView(*window, camera));
    const auto viewController = createWholeAppController(view);

    Debug("Add event listeners");
    window.addEventListener(view.get());
    window.addEventListener(viewController.get());
    window.addEventListener(camera.get());
    window.show();

    Debug("Start main loop");
    auto const result = window.messageLoop();
    Debug("Exit with result: " + std::to_string(result));

    vl::VisualizationLibrary::shutdown();
    return result;
}
catch (const std::exception& ex)
{
    Error(ex.what());
    return -1;
}
