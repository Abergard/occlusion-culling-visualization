#include "InformationMenu.hpp"

#include <vlCore/Say.hpp>
#include <vlCore/Vector3.hpp>
#include <vlGraphics/Effect.hpp>
#include <vlGraphics/FontManager.hpp>
#include <vlGraphics/GeometryPrimitives.hpp>
#include <vlGraphics/OpenGLContext.hpp>

#include "utils/vl/Log.hpp"
#include "utils/vl/MakeRef.hpp"

namespace ocv
{
namespace
{
// clang-format off
constexpr auto hTxt =   "[  H  ] hide menu           ";
constexpr auto spcTxt = "[ SPC ] mini view status    ";
constexpr auto tabTxt = "[ TAB ] active user         ";
constexpr auto vTxt =   "[  V  ] user in main view   ";
constexpr auto occTxt = "[  1  ] occlusion culling   ";
constexpr auto obsTxt = "[  2  ] observator prieview ";
constexpr auto wirTxt = "[  3  ] occluded wire mode  ";
constexpr auto abpTxt = "[  B  ] player AABB mode    ";
constexpr auto aboTxt = "[  G  ] observator AABB mode";
constexpr auto entTxt = "[ENTER] enter edit window mode";
constexpr auto enxTxt = "[ENTER] exit edit window mode ";
constexpr auto escTxt = "[ ESC ] close application     ";

vl::String getClosedMenu()
{
    return vl::Say("[ H ] show menu");
}
vl::String getOpened(const std::string& activeMiniView,
                     const std::string& activeUser,
                     const std::string& mainView,
                     const std::string& occlusionCullingState,
                     const std::string& observatorPreviewState,
                     const std::string& wireState,
                     const std::string& playerAbbState,
                     const std::string& observatorAbbState)
{
    return vl::Say("%s\n"
                   "  %s\n"
                   "  %s : %s\n"
                   "  %s : %s\n\n"
                   "  %s\n"
                   "  %s : %s\n"
                   "  %s : %s\n"
                   "  %s : %s\n\n"
                   "  %s\n"
                   "  %s : %s\n"
                   "  %s : %s\n"
                   "  %s : %s\n\n"
                   "  %s\n"
                   "  %s\n"
                   "  %s\n")
           << hTxt
           << "Player key actions:"
           << occTxt << occlusionCullingState
           << abpTxt << playerAbbState
           << "Observator key actions:"
           << obsTxt << observatorPreviewState
           << wirTxt << wireState
           << aboTxt << observatorAbbState
           << "Scene key actions:"
           << spcTxt << activeMiniView
           << tabTxt  << activeUser
           << vTxt    << mainView
           << "Application key actions:"
           << entTxt
           << escTxt;
}

vl::String getMenuWhenEditorMode()
{
    return vl::Say("%s\n"
                   "  %s\n"
                   "  %s\n")
        << "< Now you can modify the window or use actions below >"
        << enxTxt
        << escTxt;
}

std::string toStatus(bool status)
{
    return status ? "enabled" : "disabled";
}
// clang-format on
}
InformationMenu::InformationMenu(
    vl::OpenGLContext* context,
    std::shared_ptr<OcclusionStatistics> statisticScene,
    DoubleCamera& camera,
    std::shared_ptr<PlayerVisualizationState> playerState,
    std::shared_ptr<ObservatorVisualizationState> observatorState,
    std::shared_ptr<bool> preview,
    std::shared_ptr<ViewType> viewType,
    vl::ActorTreeAbstract* playerTree,
    vl::ActorTreeAbstract* observatorTree)
    : openglContext{context},
      statistics{std::move(statisticScene)},
      doubleCamera{camera},
      playerVisualizationState{std::move(playerState)},
      observatorVisualizationState{std::move(observatorState)},
      previewEnabled{std::move(preview)},
      occlusionViewType{std::move(viewType)},
      playerText{createMenu(playerTree, 0x01000000)},
      observatorText{createMenu(observatorTree, 0x01000000)}
{
    Trace();
    if (!preview)
    {
        Debug("not enabled");
    }
    else
    {
        Debug("enabled");
    }

    if (!previewEnabled)
    {
        Debug("not enabled");
    }
    else
    {
        Debug("enabled");
    }
}

void InformationMenu::showOrHide()
{
    isOptionMenuOpen = !isOptionMenuOpen;
}

void InformationMenu::updateWindowTitle()
{
    fps.update();
    openglContext->setWindowTitle(
        vl::Say("[%.1n fps] Occlusion ration = %.1n%% (%n/%n)\n")
        << fps.get() << statistics->ratio() << statistics->nonOccluded()
        << statistics->total());
}

void InformationMenu::render()
{
    updateWindowTitle();
    updateMenu(*occlusionViewType, *previewEnabled);
}

void InformationMenu::updateMenu(const ViewType occlusionViewType,
                                 const bool isSecondViewActivated)
{
    clearMenu();
    if (auto menu = getActiveMenu(occlusionViewType))
    {
        menu->setText(
            getCurrentMenuContent(occlusionViewType, isSecondViewActivated));
    }
    else
    {
        Error("Active text unavailable!");
    }
}

void InformationMenu::clearMenu()
{
    playerText->setText("");
    observatorText->setText("");
}

vl::Text* InformationMenu::getActiveMenu(const ViewType occlusionViewType)
{
    switch (occlusionViewType)
    {
    case ViewType::Player:
        return playerText.get();

    case ViewType::Observator:
        return observatorText.get();
    }

    return nullptr;
}

vl::String InformationMenu::getCurrentMenuContent(
    const ViewType occlusionViewType,
    const bool isSecondViewActivated) const
{
    const auto activeUser = doubleCamera.activeCamera();
    if (activeUser == CameraType::Editor)
    {
        return getMenuWhenEditorMode();
    }

    if (isOptionMenuOpen)
    {
        auto activeUserName = toString(activeUser);
        auto mainViewName = toString(occlusionViewType);
        return getOpened(
            toStatus(isSecondViewActivated),
            std::move(activeUserName),
            std::move(mainViewName),
            toStatus(playerVisualizationState->occlusionCullingState),
            toStatus(observatorVisualizationState->observatorState),
            toStatus(observatorVisualizationState->wireState),
            toStatus(playerVisualizationState->aabbState),
            toStatus(observatorVisualizationState->aabbState));
    }

    return getClosedMenu();
}

vl::ref<vl::Text> InformationMenu::createMenu(vl::ActorTreeAbstract* tree,
                                              const unsigned int mask)
{
    Trace();

    auto text = make_ref<vl::Text>();
    text->setText("");
    text->setFont(vl::defFontManager()->acquireFont(
        "/font/bitstream-vera/VeraMono.ttf", 10));
    text->setAlignment(vl::AlignLeft | vl::AlignTop);
    text->setViewportAlignment(vl::AlignLeft | vl::AlignTop);
    text->setTextAlignment(vl::TextAlignLeft);
    text->translate(+5, -10, 0);
    text->setColor(vl::black);
    text->setMode(vl::Text2D);
    text->setBackgroundEnabled(true);

    auto effect = make_ref<vl::Effect>();
    effect->shader()->enable(vl::EN_BLEND);
    auto textActor = tree->addActor(text.get(), effect.get());
    textActor->setOccludee(false);
    textActor->setEnableMask(mask);
    return text;
}
}
