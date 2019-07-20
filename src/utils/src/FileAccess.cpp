#include "FileAccess.hpp"

#include "StandardFileAccess.hpp"

namespace ocv
{
std::unique_ptr<FileAccess> createStandardFileAccess()
{
    return std::make_unique<StandardFileAccess>();
}
}
