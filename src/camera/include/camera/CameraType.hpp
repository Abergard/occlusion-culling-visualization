#pragma once

#include <iosfwd>
#include <string>

namespace ocv
{
enum class CameraType
{
    Player,
    Observator,
    Editor
};

inline std::string toString(const CameraType camera)
{
    switch (camera)
    {
    case CameraType::Player:
        return "player    ";

    case CameraType::Observator:
        return "observator";

    case CameraType::Editor:
        return "editor    ";
    }
    return "unknown camera";
}

inline std::ostream& operator<<(std::ostream& out, const CameraType camera)
{
    return out << toString(camera);
}
}
