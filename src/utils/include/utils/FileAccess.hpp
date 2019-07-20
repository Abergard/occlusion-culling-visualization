#pragma once

#include <sstream>
#include <memory>

namespace ocv
{
class FileAccess
{
public:
    virtual std::string read(const std::string& fileName) const = 0;
};

std::unique_ptr<FileAccess> createStandardFileAccess();
}
