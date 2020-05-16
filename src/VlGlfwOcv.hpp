#pragma once

#include <memory>
#include <string>

#include <vlCore/VisualizationLibrary.hpp>

#include "camera/DoubleCamera.hpp"
#include "input/VlController.hpp"
#include "utils/vl/Log.hpp"
#include "view/VisualizationView.hpp"
#include "window/Window.hpp"
#include "utils/vl/MakeRef.hpp"

struct ScreenSize
{
    int width;
    int height;
};

// ScreenSize getFullScreenSize()
// {
//     return ScreenSize{GetSystemMetrics(SM_CXSCREEN),
//                       GetSystemMetrics(SM_CYSCREEN)};
// }

int run_app(const ScreenSize& mainScreen)
{
    Debug("Win32 main");

    Debug("width: " + std::to_string(mainScreen.width));
    Debug("height: " + std::to_string(mainScreen.height));

    constexpr auto windowTitle{"Occlusion Culling"};

    const std::unique_ptr<ocv::Window> window = ocv::createGlfwWindow(
        windowTitle, mainScreen.width, mainScreen.height);
    auto camera = ocv::make_ref<ocv::DoubleCamera>(*window);
    auto view = ocv::make_ref<ocv::VisualizationView>(
        createVisualizationView(*window, *camera));
    auto viewController = createWholeAppController(*view);

    Debug("Add event listeners");
    window->addEventListener(view.get());
    window->addEventListener(viewController.get());
    window->addEventListener(camera.get());
    window->show();

    Debug("Start main loop");
    auto const result = window->messageLoop();
    Debug("Exit with result: " + std::to_string(result));
    return result;
}

int start(const ScreenSize& mainScreen)
try
{
    vl::VisualizationLibrary::init();
    const auto result = run_app(mainScreen);
    vl::VisualizationLibrary::shutdown();
    return result;
}
catch (const std::exception& ex)
{
    Error(ex.what());
    return -1;
}
