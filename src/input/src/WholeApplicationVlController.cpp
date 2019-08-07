#include "WholeApplicationVlController.hpp"

#include <tuple>

#include <vlCore/Time.hpp>

#include "ExitApplication.hpp"
#include "ToggleActiveView.hpp"
#include "ToggleEditorMode.hpp"
#include "ToggleMenu.hpp"
#include "ToggleObserverAABBDraw.hpp"
#include "ToggleOcvAlgorithm.hpp"
#include "TogglePlayerAABBDraw.hpp"
#include "ToggleSecondView.hpp"
#include "ToggleView.hpp"
#include "ToggleVisualizationEffect.hpp"
#include "ToggleWireMode.hpp"
#include "utils/vl/Log.hpp"
#include "view/VisualizationView.hpp"
#include "window/Window.hpp"

namespace ocv
{
namespace
{
template <vl::EKey Key, typename Command>
struct VlPair
{
    using key_t = vl::EKey;
    using value_t = Command;

    static constexpr vl::EKey key_v{Key};
};

template <typename Base, typename... Pair, typename... Args>
auto createMap(Args&&... args)
{
    using pair_t = typename std::tuple_element<0, std::tuple<Pair...>>::type;

    std::map<typename pair_t::key_t, std::unique_ptr<Base>> m{};
    ((m[Pair::key_v] = std::make_unique<typename Pair::value_t>(args...)), ...);
    return m;
}
}

WholeApplicationVlController::WholeApplicationVlController(
    std::shared_ptr<VisualizationView> view)
    : commands{createMap<VisualizationCommand,
                          VlPair<vl::Key_1, ToggleOcvAlgorithm>,
                          VlPair<vl::Key_2, ToggleVisualizationEffect>,
                          VlPair<vl::Key_3, ToggleWireMode>,
                          VlPair<vl::Key_B, TogglePlayerAABBDraw>,
                          VlPair<vl::Key_G, ToggleObserverAABBDraw>,
                          VlPair<vl::Key_H, ToggleMenu>,
                          VlPair<vl::Key_V, ToggleView>,
                          VlPair<vl::Key_Tab, ToggleActiveView>,
                          VlPair<vl::Key_Return, ToggleEditorMode>,
                          VlPair<vl::Key_Space, ToggleSecondView>,
                          VlPair<vl::Key_Escape, ExitApplication>>(view)},
      occlusionVisualizationView{std::move(view)}
{
}

void WholeApplicationVlController::keyPressEvent(unsigned short /*ch*/,
                                                 const vl::EKey key)
{
    const auto commandIt = commands.find(key);
    if (commandIt != commands.end())
    {
        commandIt->second->execute();
    }
}
}
