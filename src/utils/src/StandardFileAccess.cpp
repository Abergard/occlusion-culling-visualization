#include "StandardFileAccess.hpp"

#include <cstring>
#include <cerrno>
#include <fstream>
#include <iostream>

namespace ocv
{
std::string StandardFileAccess::read(const std::string& fileName) const
{
    std::clog << "Trying to read: " << fileName << '\n';
    if (auto&& in = std::ifstream(fileName, std::ios::in | std::ios::binary))
    {
        std::string content;
        in.seekg(0, std::ios::end);
        content.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&content[0], content.size());
        in.close();
        return content;
    }
    std::clog << "ERR log " << std::strerror(errno) << '\n';
    throw(errno); // TODO: Uncatchable exception. Add test and custom exception
}
}
