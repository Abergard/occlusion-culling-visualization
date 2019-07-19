#pragma once

#include "FileAccess.hpp"

#include <gmock/gmock.h>

namespace ocv
{
class MockFileAccess : public FileAccess
{
public:
    MOCK_CONST_METHOD1(read, std::string(const std::string&));
};
}
