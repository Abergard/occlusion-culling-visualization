#pragma once

#include <iosfwd>

namespace ocv
{
enum class ViewType
{
    Player,
    Observator
};

inline std::string toString(const ViewType view)
{
    switch (view)
    {
    case ViewType::Player:
        return "player";

    case ViewType::Observator:
        return "observator";
    }
    return "unknown view";
}

inline std::ostream& operator<<(std::ostream& out, const ViewType view)
{
    return out << toString(view);
}

}
