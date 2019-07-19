#pragma once

#include "FileAccess.hpp"

namespace ocv
{
class StandardFileAccess : public FileAccess
{
public:
    std::string read(const std::string& fileName) const override;
};
}
